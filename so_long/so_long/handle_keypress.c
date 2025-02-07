#include "so_long.h"

int handle_keypress(int keycode, t_game *game)
{
    printf("handel %d\n", keycode);
    int dx = 0, dy = 0;

    // Handle keypresses
    if (keycode == 65307) // Escape key
    {
        free_game(game);
        exit(0);
    }
    else if (keycode == 65361) // Left arrow
        dx = -1;
    else if (keycode == 65363) // Right arrow
        dx = 1;
    else if (keycode == 65362) // Up arrow
        dy = -1;
    else if (keycode == 65364) // Down arrow
        dy = 1;

    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    // Check for valid movement
    if (new_x < 0 || new_x >= game->map_width || new_y < 0 || new_y >= game->map_height)
        return (0); // Ignore movement outside the map

    // Check if the new position is a wall
    if (game->map[new_y][new_x] == '1')
        return (0);

    // Handle collectibles
    if (game->map[new_y][new_x] == 'C')
        game->collectibles--;

    // Handle exit condition
    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
    {
        printf("You win!\n");
        mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE / 2 - 50, game->map_height * TILE_SIZE / 2, 0x00FF00, "You win!");
        mlx_do_sync(game->mlx); // Ensure the message is displayed
        sleep(2); // Wait for 2 seconds before exiting
        free_game(game);
        exit(0);
    }

    // Update player position
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
window(game->mlx, game->win);
    render_map(game);
    // Re-render the map
    mlx_clear_

    return (0);
}