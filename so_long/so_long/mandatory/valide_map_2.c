/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/12 09:05:08 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void add_one(t_valid *sume, char c)
{
    if (c == '1')
        sume->wall++;
    else if (c == '0')
        sume->space++;
    else if (c == 'P')
        sume->player++;
    else if (c == 'E')
        sume->exit++;
    else if (c == 'C')
        sume->collectibl++;
}

void get_number(t_valid *sume, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            add_one(sume, map[i][j]);
            j++;
        }
        i++;
    }
}

void validate_component_map(t_game *game)
{
    t_valid *sume;

    sume = (t_valid *)malloc(sizeof(t_valid));
    if (!sume)
    {
        printf("Memory allocation failed!\n");
        free_game(game);
        exit(1);
    }

    sume->wall = 0;
    sume->space = 0;
    sume->exit = 0;
    sume->player = 0;
    sume->collectibl = 0;

    get_number(sume, game->map);
    if (sume->wall < 1 || sume->player != 1 || sume->collectibl < 1 || sume->exit != 1 || sume->space < 1)
    {
        printf("Error: Invalid component in map!\n");
        printf("Walls: %d, Players: %d, Collectibles: %d, Exits: %d, Spaces: %d\n",
               sume->wall, sume->player, sume->collectibl, sume->exit, sume->space);
        free(sume);
        free_game(game);
        exit(1);
    }

    free(sume);
}
