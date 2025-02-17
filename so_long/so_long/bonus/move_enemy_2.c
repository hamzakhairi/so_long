/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:47:58 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 19:12:56 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static int	count_enemies(t_game *game)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'M')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	make_change(t_game *game, int index, int i, int j)
{
	game->arr_enemy[index].enemy_x = j;
	game->arr_enemy[index].enemy_y = i;
	if (index % 2 == 0)
	{
		game->arr_enemy[index].direction_image = 1;
		game->arr_enemy[index].direction = 1;
	}
	else
	{
		game->arr_enemy[index].direction_image = -1;
		game->arr_enemy[index].direction = -1;
	}
}

static void	main_make_change(t_game *game, int i, int j, int *index)
{
	while (game->map[i][j])
	{
		if (game->map[i][j] == 'M')
		{
			make_change(game, *index, i, j);
			(*index)++;
		}
		j++;
	}
}

static void	init_enemies(t_game *game, int enemy_count)
{
	int	i;
	int	index;
	int	j;

	game->arr_enemy = (t_enemy *)malloc(enemy_count * sizeof(t_enemy));
	if (!game->arr_enemy)
	{
		print_error("Error : Failed to allocate memory for enemies\n");
		free_game(game);
		exit(1);
	}
	game->num_enemies = enemy_count;
	i = 0;
	index = 0;
	while (game->map[i])
	{
		j = 0;
		main_make_change(game, i, j, &index);
		i++;
	}
}

void	find_enemy_positions(t_game *game)
{
	int	enemy_count;

	enemy_count = count_enemies(game);
	if (enemy_count <= 0 || !game->map)
	{
		game->arr_enemy = NULL;
		game->num_enemies = 0;
		return ;
	}
	init_enemies(game, enemy_count);
}
