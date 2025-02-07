#include "./minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TILE_SIZE 128
#define COLOR_TEXT 0xFFFFFF

void draw_colored_text(void *mlx, void *win, int x, int y, int color, char *text) {
    mlx_string_put(mlx, win, x, y, color, text);
}

void play_sound(const char *file) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("aplay", "aplay", file, NULL); // Replace "aplay" with "afplay" for macOS
        exit(1);
    }
}

void draw_dynamic_ui(t_game *game) {
    char move_str[50];
    sprintf(move_str, "Moves: %d | Collectibles: %d", game->moves, game->collectibles);
    draw_colored_text(game->mlx, game->win, 10, 10, COLOR_TEXT, move_str);
}

// Integrate the above suggestions to make the game more attractive:
int main(void) {
    t_game game;

    init_game(&game, "maps/map1.ber");
    draw_map(&game);

    // Optionally, play background music
    play_sound("background_music.wav"); 

    // Dynamic update to the move counter and stats
    mlx_loop_hook(game.mlx, (int (*)(void *))draw_dynamic_ui, &game);

    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);
    return (0);
}
