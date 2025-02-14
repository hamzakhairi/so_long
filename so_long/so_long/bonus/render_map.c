/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:41:00 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/14 18:05:41 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, void *img, int x, int y)
{
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	validate_put_game(t_game *game, int x, int y, char c)
{
	void	*img;

	img = NULL;
	if ('1' == c)
		img = game->img_wall;
	else if ('0' == c)
		img = game->img_empty;
	else if ('P' == c)
		img = game->img_player;
	else if ('C' == c)
		img = game->img_collect;
	else if ('E' == c)
		img = game->img_exit;
	else if ('M' == c)
		img = game->img_enemy;
	put_image(game, img, x, y);
}

void	render_map(t_game	*game)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			validate_put_game(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}
