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
    int i = 0;
    int j  =0;
    char **copy = malloc(sizeof(char *) * (rows + 1));
    if (!copy)
        return (NULL);

    while (map[i])
    {
        copy[i] = ft_strdup_str(map[i]);
        if (!copy[i])
        {
            j = 0;
            free_map(copy);
            return (NULL);
        }
        i++;
    }
    copy[rows] = NULL;
    return (copy);
}

void flood_fill(char **map, int x, int y)
{
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;
    map[y][x] = 'F';

    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

int check_copy_map(char **map, int row)
{
    int i = 0;
    int j =0;

    while (i < row)
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'E' || map[i][j] == 'C')
            {
                printf("+++ %c ++\n", map[i][j]);
                return 0;
            }
            j++;
        }
        i++;
    }
    return 1;
}

void validate_map(char **map)
{
    t_point player = find_player(map);
    if (player.x == -1 || player.y == -1)
    {
        printf("Error: Player not found in the map.\n");
        free(map);
        exit(1);
    }
    t_map size = size_map(map);
    char **map_copy = copy_map(map, size.i);
    if (!map_copy)
    {
        printf("Error: Failed to copy the map.\n");
        free(map);
        exit(1);
    }

    flood_fill(map_copy, player.x, player.y);
    for (int i = 0; map_copy[i]; i++)
    {
        printf("%s\n", map_copy[i]);
    }
    if (!check_copy_map(map_copy, size.i))
    {
        printf("Invalide map\n");
        free(map);
        free(map_copy);
        exit(1);
    }
    free(map_copy);
}
