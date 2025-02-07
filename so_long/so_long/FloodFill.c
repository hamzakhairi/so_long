#include "so_long.h"

t_point find_player(char **map)
{
    t_point player = {-1, -1};
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                player.x = j;
                player.y = i;
                return (player);
            }
            j++;
        }
        i++;
    }
    return (player);
}

char **copy_map(char **map, int rows)
{
    char **copy = malloc(sizeof(char *) * (rows + 1));
    if (!copy)
        return (NULL);

    for (int i = 0; i < rows; i++)
    {
        copy[i] = strdup(map[i]);
        if (!copy[i])
        {
            for (int j = 0; j < i; j++)
                free(copy[j]);
            free(copy);
            return (NULL);
        }
    }
    copy[rows] = NULL;
    return (copy);
}

void flood_fill(char **map, int x, int y, t_valid *game)
{
    // Base cases
    if (x < 0 || y < 0 || !map[y] || !map[y][x] || map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'E')
        return;

    // Mark the cell as visited
    char current = map[y][x];
    map[y][x] = 'X';

    // Debug print
    printf("Visiting cell (%d, %d): %c\n", x, y, current);

    // Update game state based on the current cell
    if (current == 'E')
    {
        game->exit_reachable = 1;
        printf("Exit found at (%d, %d)\n", x, y);
    }
    else if (current == 'C')
    {
        game->collectibles_reachable++;
        printf("Collectible found at (%d, %d)\n", x, y);
    }

    // Recursively explore neighboring cells
    flood_fill(map, x + 1, y, game); // Right
    flood_fill(map, x - 1, y, game); // Left
    flood_fill(map, x, y + 1, game); // Down
    flood_fill(map, x, y - 1, game); // Up
}

int validate_map(char **map, t_valid *game)
{
    t_point player = find_player(map);
    if (player.x == -1 || player.y == -1)
    {
        printf("Error: Player not found in the map.\n");
        return (0);
    }

    char **map_copy = copy_map(map, game->rows);
    if (!map_copy)
    {
        printf("Error: Failed to copy the map.\n");
        return (0);
    }

    game->exit_reachable = 0;
    game->collectibles_reachable = 0;

    flood_fill(map_copy, player.x, player.y, game);

    for (int i = 0; map_copy[i]; i++)
        free(map_copy[i]);
    free(map_copy);

    if (!game->exit_reachable || game->collectibles_reachable != game->collectibl)
    {
        printf("Error: Map is invalid (exit not reachable after collecting all collectibles).\n");
        return (0);
    }

    return (1);
}
