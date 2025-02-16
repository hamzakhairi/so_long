/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:22:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/16 15:43:00 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void update_enemy_direction(t_game *game, int i)
{
    int img_width;
    int img_height;
    void *new_img;

    if (game->arr_enemy[i].direction_image == 1)
        new_img = mlx_xpm_file_to_image(game->mlx, "./image/playeer1.xpm", &img_width, &img_height);
    else
        new_img = mlx_xpm_file_to_image(game->mlx, "./image/playeer2.xpm", &img_width, &img_height);

    if (new_img)
    {
        if (game->img_enemy)
            mlx_destroy_image(game->mlx, game->img_enemy);
        game->img_enemy = new_img;
        game->arr_enemy[i].direction_image *= -1;
    }
}

static void	if_next_tile_0(t_game *game, int i, int new_y, int new_x)
{
	game->map[game->arr_enemy[i].enemy_y][game->arr_enemy[i].enemy_x] = '0';
	game->map[new_y][new_x] = 'M';
	game->arr_enemy[i].enemy_x = new_x;
}
static void move_single_enemy(t_game *game, int i)
{
    int new_x;
    int new_y;
    char next_tile;

    new_x = game->arr_enemy[i].enemy_x + game->arr_enemy[i].direction;
    new_y = game->arr_enemy[i].enemy_y;
    if (new_x >= 0 && new_x < game->map_width)
    {
        next_tile = game->map[new_y][new_x];
        if (next_tile == '0')
            if_next_tile_0(game, i, new_y, new_x);
        else if (next_tile == 'P')
            handle_failed(game);
        else if (next_tile == '1' || next_tile == 'E' || next_tile == 'M' || next_tile == 'C')
        {
            game->arr_enemy[i].direction *= -1;
            update_enemy_direction(game, i);
        }
    }
    else
    {
        game->arr_enemy[i].direction *= -1;
        update_enemy_direction(game, i);
    }
}

void move_enemies(t_game *game)
{
    static int counter = 0;
    int i;

    counter++;
    if (counter < 15000)
        return;
    counter = 0;

    i = 0;
    while (i < game->num_enemies)
    {
        move_single_enemy(game, i);
        i++;
    }
    mlx_clear_window(game->mlx, game->win);
    render_map(game);
}

int	game_loop(t_game *game)
{
	if (game->arr_enemy == NULL)
		find_enemy_positions(game);
	move_enemies(game);
	return (0);
}
