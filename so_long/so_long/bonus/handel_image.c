/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:49:01 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/13 11:42:50 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void return_imag(t_game *game, int dx, int dy)
{
    int	img_width;
	int	img_height;
    
    if (dx == -1 && dy == 0)
        game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./image/playeer1.xpm", &img_width, &img_height);
    else if (dx == 1 && dy == 0)
        game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./image/playeer2.xpm", &img_width, &img_height);
    else if (dx == 0 && dy == -1)
        game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./image/playeer3.xpm", &img_width, &img_height);
    else if (dx == 0 && dy == 1)
        game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./image/playeer4.xpm", &img_width, &img_height);
}
void handel_image_player(t_game *game, int dx, int dy)
{
    return_imag(game, dx, dy);
    if (!game->img_player)
    {
        printf("[1] Error: Failed to load one or more XPM images\n");
		free_images(game);
		exit(1);
    }
}
