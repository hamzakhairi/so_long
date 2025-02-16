/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:49:01 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/16 15:27:42 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tow_handel_1(t_game *game, int dx, int dy)
{
	int	img_width;
	int	img_height;

	if (dx == -1 && dy == 0)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./image/playeer1.xpm", &img_width, &img_height);
	}
	else if (dx == 1 && dy == 0)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./image/playeer2.xpm", &img_width, &img_height);
	}
}

void	tow_handel_2(t_game *game, int dx, int dy)
{
	int	img_width;
	int	img_height;

	if (dx == 0 && dy == -1)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./image/playeer3.xpm", &img_width, &img_height);
	}
	else if (dx == 0 && dy == 1)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./image/playeer4.xpm", &img_width, &img_height);
	}
}

void	return_imag(t_game *game, int dx, int dy)
{
	if ((dx == -1 && dy == 0) || (dx == 1 && dy == 0))
		tow_handel_1(game, dx, dy);
	else if ((dx == 0 && dy == -1) || (dx == 0 && dy == 1))
		tow_handel_2(game, dx, dy);
}

void	handel_image_player(t_game *game, int dx, int dy)
{
	return_imag(game, dx, dy);
	if (!game->img_player)
	{
		printf("[1] Error: Failed to load one or more XPM images\n");
		free_images(game);
		exit(1);
	}
}
