/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:46:46 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/06 21:19:20 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(char **map)
{
    int i = 0;
    if (!map)
        return;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}


void free_images(t_game *game)
{
    if (game->img_wall)
        mlx_destroy_image(game->mlx, game->img_wall);
    if (game->img_empty)
        mlx_destroy_image(game->mlx, game->img_empty);
    if (game->img_player)
        mlx_destroy_image(game->mlx, game->img_player);
    if (game->img_collect)
        mlx_destroy_image(game->mlx, game->img_collect);
    if (game->img_exit)
        mlx_destroy_image(game->mlx, game->img_exit);
}