#include "./minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define TILE_SIZE 32 // Match tile size to image size

typedef struct s_game {
    void *mlx;
    void *win;
    void *img_wall;
    void *img_player;
    void *img_collect;
    void *img_exit;
    void *img_empty;
    char **map;
    int map_width;
    int map_height;
    int player_x;
    int player_y;
    int collectibles;
    int moves;
} t_game;

// Function to read the map into a 2D array
char **read_map(const char *file, int *width, int *height) {
    char **map;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    // Count lines and get width
    *width = *height = 0;
    while ((nread = getline(&line, &len, fp)) != -1) {
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0'; // Remove newline
        if (!*width) {
            *width = nread - 1; // Set map width
            printf("Map width: %d\n", *width); // Debug: Print map width
        } else if (nread - 1 != *width) {
            fprintf(stderr, "Error: Map is not rectangular. Expected width %d, got %zd\n", *width, nread - 1);
            exit(1);
        }
        (*height)++;
        printf("Line %d: %s\n", *height, line); // Debug: Print each line
    }
    fseek(fp, 0, SEEK_SET); // Reset file pointer

    // Allocate memory for the map
    map = malloc(sizeof(char *) * (*height));
    if (!map) {
        fprintf(stderr, "Error: Failed to allocate memory for map\n");
        exit(1);
    }
    for (int i = 0; i < *height; i++) {
        getline(&line, &len, fp);
        if (line[*width] == '\n')
            line[*width] = '\0';
        map[i] = strdup(line); // Copy the line
        if (!map[i]) {
            fprintf(stderr, "Error: Failed to allocate memory for map line\n");
            exit(1);
        }
    }
    free(line);
    fclose(fp);
    return map;
}

// Validate the map
void validate_map(t_game *game) {
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;

    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            char tile = game->map[y][x];
            if (tile == 'P') player_count++;
            else if (tile == 'E') exit_count++;
            else if (tile == 'C') collectible_count++;
            else if (tile != '0' && tile != '1') {
                fprintf(stderr, "Error: Invalid tile '%c' in map\n", tile);
                exit(1);
            }
        }
    }

    if (player_count != 1 || exit_count != 1 || collectible_count < 1) {
        fprintf(stderr, "Error: Invalid map configuration\n");
        exit(1);
    }
}

// Draw the move counter
void draw_move_counter(t_game *game) {
    char move_str[20];
    sprintf(move_str, "Moves: %d", game->moves);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, move_str);
    printf("Player position: (%d, %d)\n", game->player_x, game->player_y); // Debug: Print player position
}

// Draw the entire map
void draw_map(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            char tile = game->map[y][x];
            if (tile == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->img_empty, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->img_collect, x * TILE_SIZE, y * TILE_SIZE);
            else if (tile == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    draw_move_counter(game);
}

// Move player and handle events
int handle_keypress(int keycode, t_game *game) {
    int dx = 0, dy = 0;
    if (keycode == 65307) // Escape key
        exit(0);
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
    if (new_x < 0 || new_x >= game->map_width || new_y < 0 || new_y >= game->map_height) {
        return (0); // Ignore movement outside the map
    }

    if (game->map[new_y][new_x] != '1') {
        if (game->map[new_y][new_x] == 'C') {
            game->collectibles--;
        }
        if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) {
            printf("You win!\n");
            mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE / 2 - 50, game->map_height * TILE_SIZE / 2, 0x00FF00, "You win!");
            mlx_loop(game->mlx); // Keep the window open
            exit(0);
        }

        // Update player position
        game->map[game->player_y][game->player_x] = '0';
        game->map[new_y][new_x] = 'P';
        game->player_x = new_x;
        game->player_y = new_y;
        game->moves++;

        // Redraw the map
        mlx_clear_window(game->mlx, game->win);
        draw_map(game);
    }
    return (0);
}

// Initialize images and game
void init_game(t_game *game, const char *map_file) {
    game->mlx = mlx_init();
    game->map = read_map(map_file, &game->map_width, &game->map_height);
    validate_map(game);

    // Save the original map dimensions
    int original_width = game->map_width;
    int original_height = game->map_height;

    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long");

    // Load images with error checking
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &game->map_width, &game->map_height);
    if (!game->img_wall) {
        fprintf(stderr, "Error: Failed to load wall.xpm\n");
        exit(1);
    }
    game->img_empty = mlx_xpm_file_to_image(game->mlx, "empty.xpm", &game->map_width, &game->map_height);
    if (!game->img_empty) {
        fprintf(stderr, "Error: Failed to load empty.xpm\n");
        exit(1);
    }
    game->img_player = mlx_xpm_file_to_image(game->mlx, "player.xpm", &game->map_width, &game->map_height);
    if (!game->img_player) {
        fprintf(stderr, "Error: Failed to load player.xpm\n");
        exit(1);
    }
    game->img_collect = mlx_xpm_file_to_image(game->mlx, "collect.xpm", &game->map_width, &game->map_height);
    if (!game->img_collect) {
        fprintf(stderr, "Error: Failed to load collect.xpm\n");
        exit(1);
    }
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &game->map_width, &game->map_height);
    if (!game->img_exit) {
        fprintf(stderr, "Error: Failed to load exit.xpm\n");
        exit(1);
    }

    // Reset map dimensions to their original values
    game->map_width = original_width;
    game->map_height = original_height;

    game->collectibles = 0;
    game->moves = 0;

    // Find player and collectible count
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == 'P') {
                game->player_x = x;
                game->player_y = y;
            }
            if (game->map[y][x] == 'C')
                game->collectibles++;
        }
    }

    printf("Player position: (%d, %d)\n", game->player_x, game->player_y); // Debug: Print player position
}

int main(void) {
    t_game game;

    init_game(&game, "maps/map1.ber");
    draw_map(&game);
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);

    return (0);
}