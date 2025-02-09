/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:46:13 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/08 16:05:11 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"




t_map size_map(char **map)
{
    t_map map_s = {0, 0};
    int prev = 0;

    while (map[map_s.i])
    {
        map_s.j = 0;
        while (map[map_s.i][map_s.j])
            map_s.j++;
        if (prev == 0)
            prev = map_s.j;
        if (prev != map_s.j)
        {
            printf("[2] Invalid map\n");
            free_map(map);
            exit(1);
        }
        map_s.i++;
    }
    if (map_s.j < map_s.i)
    {
        printf("Map is not rectangular\n");
        free_map(map);
        exit(1);
    }
    return (map_s);
}

int valid_first_wall_and_last_wall(char **map)
{
    t_map size = size_map(map);
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        if (i == 0 || i == size.i - 1)
        {
            while (map[i][j])
            {
                if (map[i][j] != '1')
                {
                    printf("Invalid wall at row %d, column %d\n", i, j);
                    free_map(map);
                    return (0);
                }
                j++;
            }
        }
        else
        {
            while (map[i][j])
            {
                if ((j == 0 || j == size.j - 1) && map[i][j] != '1')
                {
                    printf("Invalid wall at row %d, column %d\n", i, j);
                    free_map(map);
                    return (0);
                }
                j++;
            }
        }
        i++;
    }
    return (1);
}

t_valid valide(char **map)
{
    t_valid game = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] == 'E')
                && (map[i][j] == 'P') && (map[i][j] == 'C'))
            {
                printf("[1] Bad character in map %d %d %c\n", i, j, map[i][j]);
                free_map(map);
                exit(1);
            }
            j++;
        }
        i++;
    }
    game.rows = i;

    if (!valid_first_wall_and_last_wall(map))
    {
        free_map(map);
        exit(1);
    }

    return game;
}









