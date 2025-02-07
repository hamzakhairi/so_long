#include "so_long.h"

void render_map(t_game *game)
{
    printf("game->map_height[2] %d\n", game->map_height);
    printf("game->map_width[2] %d\n", game->map_width);
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            void *img = NULL;
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
            else
                break;
            if (img)
                mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

t_map_game print_map1(char **map, int *player_x, int *player_y)
{
    t_map_game position = {0, 0};

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
            printf("%c", map[position.y][position.x]);
            position.x++;
        }
        printf("\n");
        position.y++;
    }
    return position;
}


void init_game(t_game *game, char *file_name)
{
    int img_width = 0, img_height = 0;

    game->mlx = mlx_init();
    if (!game->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize MLX\n");
        exit(1);
    }

    game->map = read_map(file_name);
    if (!game->map)
    {
        fprintf(stderr, "Error: Failed to load map\n");
        exit(1);
    }

    t_map_game map_w_h = print_map1(game->map, &game->player_x, &game->player_y);
    game->map_height = map_w_h.y;
    game->map_width = map_w_h.x;

    printf("Map dimensions: %d (width) x %d (height)\n", game->map_width, game->map_height);
    printf("Player position: (%d, %d)\n", game->player_x, game->player_y);

    game->collectibles = 0;
    game->moves = 0;

    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
    {
        fprintf(stderr, "Error: Failed to create window\n");
        free_map(game->map);
        free(game);
        exit(1);
    }

    game->img_wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &img_width, &img_height);
    game->img_empty = mlx_xpm_file_to_image(game->mlx, "empty.xpm", &img_width, &img_height);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "player.xpm", &img_width, &img_height);
    game->img_collect = mlx_xpm_file_to_image(game->mlx, "collect.xpm", &img_width, &img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &img_width, &img_height);

    if (!game->img_wall || !game->img_empty || !game->img_player || !game->img_collect || !game->img_exit)
    {
        fprintf(stderr, "Error: Failed to load one or more XPM images\n");
        free_images(game);
        free_map(game->map);
        mlx_destroy_window(game->mlx, game->win);
        free(game);
        exit(1);
    }

    printf("All images loaded successfully!\n");
}