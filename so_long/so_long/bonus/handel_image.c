/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:49:01 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 15:06:20 by hkhairi          ###   ########.fr       */
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
				"./texter/playeer_left.xpm", &img_width, &img_height);
	}
	else if (dx == 1 && dy == 0)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./texter/playeer_rigth.xpm", &img_width, &img_height);
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
				"./texter/playeer_up.xpm", &img_width, &img_height);
	}
	else if (dx == 0 && dy == 1)
	{
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = mlx_xpm_file_to_image(game->mlx,
				"./texter/playeer_down.xpm", &img_width, &img_height);
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
		print_error("Error: Failed to load one or more XPM images\n");
		free_images(game);
		exit(1);
	}
}
