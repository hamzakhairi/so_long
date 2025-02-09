/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:44:43 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/08 15:20:35 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map_game	get_map_info(char **map, int *player_x,
	int *player_y, int *collectibles)
{
	t_map_game	position;

	position.x = 0;
	position.y = 0;
	while (map[position.y])
	{
		position.x = 0;
		while (map[position.y][position.x])
		{
			if (map[position.y][position.x] == 'P')
			{
				*player_x = position.x;
				*player_y = position.y;
			}
			if (map[position.y][position.x] == 'C')
				(*collectibles)++;
			position.x++;
		}
		position.y++;
	}
	return (position);
}

void	load_images(t_game	*game)
{
	int	img_width;
	int	img_height;

	img_width = 0;
	img_height = 0;
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"./image/wall.xpm", &img_width, &img_height);
	game->img_empty = mlx_xpm_file_to_image(game->mlx,
			"./image/empty.xpm", &img_width, &img_height);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./image/player.xpm", &img_width, &img_height);
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"./image/collect.xpm", &img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"./image/exit.xpm", &img_width, &img_height);
	if (!game->img_wall || !game->img_empty || !game->img_player
		|| !game->img_collect || !game->img_exit)
	{
		printf("Error: Failed to load one or more XPM images\n");
		free_images(game);
		exit(1);
	}
}

void	exit_if_filed(t_game	*game)
{
	printf("Error: Failed to create window\n");
	free_map(game->map);
	free(game);
	exit(1);
}

void	init_game(t_game *game, char *file_name)
{
	t_map_game	map_info;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	game->map = read_map(file_name);
	if (!game->map)
	{
		printf("Error: Failed to load map\n");
		exit(1);
	}
	valide(game->map);
	game->collectibles = 0;
	map_info = get_map_info(game->map, &game->player_x,
			&game->player_y, &game->collectibles);
	game->map_height = map_info.y;
	game->map_width = map_info.x;
	game->moves = 0;
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
		exit_if_filed(game);
	load_images(game);
}
