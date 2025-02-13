/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:22:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/13 11:44:28 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void find_enemy_positions(t_game *game) {
    int i = 0;
    int j = 0;
    int enemy_count = 0;

    // First, count the number of enemies
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j]) {
            if (game->map[i][j] == 'M') {
                enemy_count++;
            }
            j++;
        }
        i++;
    }

    // Allocate memory for the enemies
    game->arr_enemy = (t_enemy *)malloc(enemy_count * sizeof(t_enemy));
    game->num_enemies = enemy_count;

    // Populate the array with enemy positions
    i = 0;
    enemy_count = 0;
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j]) {
            if (game->map[i][j] == 'M') {
                game->arr_enemy[enemy_count].enemy_x = j;
                game->arr_enemy[enemy_count].enemy_y = i;
                enemy_count++;
            }
            j++;
        }
        i++;
    }
}

void move_enemies(t_game *game) {
    static int *direction = NULL;
    static int counter = 0;
    int i;

    if (direction == NULL) {
        direction = (int *)malloc(game->num_enemies * sizeof(int));
        for (i = 0; i < game->num_enemies; i++) {
            direction[i] = 1;
        }
    }

    counter++;
    if (counter < 15000) return;
    counter = 0;

	i = 0;
    while (i < game->num_enemies) {
        int new_x = game->arr_enemy[i].enemy_x + direction[i];
        int new_y = game->arr_enemy[i].enemy_y;

        if (new_x >= 0 && new_x < game->map_width) {
            char next_tile = game->map[new_y][new_x];

            if (next_tile == '0') { 
                game->map[game->arr_enemy[i].enemy_y][game->arr_enemy[i].enemy_x] = '0';
                game->map[new_y][new_x] = 'M';
                game->arr_enemy[i].enemy_x = new_x;
            }
            else if ( next_tile == 'P')
                handle_failed(game); 
            else if (next_tile == '1' || next_tile == 'E' || next_tile == 'M') {
                direction[i] = -direction[i];
			}
        } else {
            direction[i] = -direction[i];
        }
		i++;
    }

    mlx_clear_window(game->mlx, game->win);
    render_map(game);
}


int game_loop(t_game *game) {
	find_enemy_positions(game);
    move_enemies(game);
    return (0);
}
