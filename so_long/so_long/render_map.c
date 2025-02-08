/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:41:00 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/07 21:51:16 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, void *img, int x, int y)
{
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game	*game)
{
	int		y;
	int		x;
	void	*img;

	y = 0;
	x = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			img = NULL;
			if (game->map[y][x] == '1')
				img = game->img_wall;
			else if (game->map[y][x] == '0')
				img = game->img_empty;
			else if (game->map[y][x] == 'P')
				img = game->img_player;
			else if (game->map[y][x] == 'C')
				img = game->img_collect;
			else if (game->map[y][x] == 'E')
				img = game->img_exit;
			put_image(game, img, x, y);
			x++;
		}
		y++;
	}
}
