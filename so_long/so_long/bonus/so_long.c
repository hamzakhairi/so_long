/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:28:44 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/16 15:08:39 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_name(char *str, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 3;
	while (str[i])
		i++;
	if (i < 4)
	{
		printf("Invalide name map\n");
		exit(1);
	}
	i--;
	while (str[i] && str2[j])
	{
		if (str[i] != str2[j])
		{
			printf("Invalide name map\n");
			exit(1);
		}
		i--;
		j--;
	}
}

int	ft_close(t_game *game)
{
	free_game(game);
	exit(0);
}

void	free_game(t_game	*game)
{
	if (game)
		free_all_component(game);
}

void	bigen_game(t_game *game, char *str)
{
	init_game(game, str);
	render_map(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 17, 0, ft_close, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	check_name(argv[1], ".ber");
	game = malloc(sizeof(t_game));
	if (!game)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		return (1);
	}
	bigen_game(game, argv[1]);
	free_game(game);
	return (0);
}
