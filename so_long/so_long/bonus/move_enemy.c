/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:22:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/14 22:29:51 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int count_enemies(t_game *game) {
    int count = 0;
    int i = 0;

    while (game->map[i]) {
        int j = 0;
        while (game->map[i][j]) {
            if (game->map[i][j] == 'M') count++;
            j++;
        }
        i++;
    }
    return count;
}

static void init_enemies(t_game *game, int enemy_count) {
    int i = 0;
    int index = 0;

    if (enemy_count > 0)
        game->arr_enemy = (t_enemy *)malloc(enemy_count * sizeof(t_enemy));
    else
        game->arr_enemy = NULL;
    game->num_enemies = enemy_count;
    if (!game->arr_enemy) {
        printf("Failed to allocate memory for enemies\n");
        free_game(game);
        exit(1);
    }

    while (game->map[i]) {
        int j = 0;
        while (game->map[i][j]) {
            if (game->map[i][j] == 'M') {
                game->arr_enemy[index].enemy_x = j;
                game->arr_enemy[index].enemy_y = i;
                game->arr_enemy[index].direction_image = (index % 2 == 0) ? 1 : -1;
                game->arr_enemy[index].direction = (index % 2 == 0) ? 1 : -1;
                index++;
            }
            j++;
        }
        i++;
    }
    game->num_enemies = enemy_count;
}

void find_enemy_positions(t_game *game) {
    int enemy_count = count_enemies(game);
    init_enemies(game, enemy_count);
}

// static void update_enemy_direction(t_game *game, int i) {
//     int img_width, img_height;

//     if (game->arr_enemy[i].direction_image == 1) {
//         if (game->img_enemy)
//                 mlx_destroy_image(game->mlx, game->img_enemy);
//         game->img_enemy = mlx_xpm_file_to_image(game->mlx,
//             "./image/playeer1.xpm", &img_width, &img_height);
//             game->arr_enemy[i].direction_image *= -1;
//     } else {
//         if (game->img_enemy)
//                 mlx_destroy_image(game->mlx, game->img_enemy);
//         game->img_enemy = mlx_xpm_file_to_image(game->mlx,
//             "./image/playeer2.xpm", &img_width, &img_height);
//             game->arr_enemy[i].direction_image *= -1;
//     }
// }

static void update_enemy_direction(t_game *game, int i) {
    int img_width, img_height;
    void *new_img;

    if (game->arr_enemy[i].direction_image == 1) {
        new_img = mlx_xpm_file_to_image(game->mlx,
            "./image/playeer1.xpm", &img_width, &img_height);
    } else {
        new_img = mlx_xpm_file_to_image(game->mlx,
            "./image/playeer2.xpm", &img_width, &img_height);
    }

    if (new_img) { // تحميل ناجح
        if (game->img_enemy) // تدمير الصورة القديمة قبل استبدالها
            mlx_destroy_image(game->mlx, game->img_enemy);
        game->img_enemy = new_img; // استبدال الصورة الجديدة
        game->arr_enemy[i].direction_image *= -1;
    }
}


static void move_single_enemy(t_game *game, int i) {
    int new_x = game->arr_enemy[i].enemy_x + game->arr_enemy[i].direction;
    int new_y = game->arr_enemy[i].enemy_y;

    if (new_x >= 0 && new_x < game->map_width) {
        char next_tile = game->map[new_y][new_x];

        if (next_tile == '0') {
            game->map[game->arr_enemy[i].enemy_y][game->arr_enemy[i].enemy_x] = '0';
            game->map[new_y][new_x] = 'M';
            game->arr_enemy[i].enemy_x = new_x;
        } else if (next_tile == 'P') {
            handle_failed(game);
        } else if (next_tile == '1' || next_tile == 'E' || next_tile == 'M' || next_tile == 'C') {
            game->arr_enemy[i].direction *= -1;
        }
        update_enemy_direction(game, i);
        
    } else {
        game->arr_enemy[i].direction *= -1;
    }
}

void move_enemies(t_game *game) {
    static int counter = 0;
    int i = 0;

    counter++;
    if (counter < 1500) return;
    counter = 0;

    while (i < game->num_enemies) {
        move_single_enemy(game, i);
        i++;
    }

    mlx_clear_window(game->mlx, game->win);
    render_map(game);
}

int game_loop(t_game *game) {
    if (game->arr_enemy == NULL)
        find_enemy_positions(game);
    move_enemies(game);
    return 0;
}


