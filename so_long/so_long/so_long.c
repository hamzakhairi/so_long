#include "so_long.h"


void print_map(char **map)
{
    int i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}

void free_game(t_game *game)
{
    if (!game)
        return;

    // Free the map
    if (game->map)
        free_map(game->map);

    // Free images
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

    // Destroy the window and free MLX
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx); // Free MLX display
        free(game->mlx);
    }

    // Free the game struct
    free(game);
}

int main(int argc, char *argv[])
{
    t_game *game;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
        return 1;
    }
    game = malloc(sizeof(t_game));
    if (!game)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Initialize all pointers to NULL
    game->map = NULL;
    game->img_wall = NULL;
    game->img_empty = NULL;
    game->img_player = NULL;
    game->img_collect = NULL;
    game->img_exit = NULL;
    game->win = NULL;
    game->mlx = NULL;
    game->player_x = 0;
    game->player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    game->collectibles = 0;
    game->moves = 0;



    init_game(game, argv[1]);
    
    render_map(game);
    mlx_key_hook(game->win, handle_keypress, game);
    mlx_loop(game->mlx);
    free_game(game);

    return 0;
}
