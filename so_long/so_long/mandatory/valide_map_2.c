/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:09 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 19:11:47 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map size_map(t_game *game)
{
    t_map map_s;
    int prev;
    char **map;

    map_s.i = 0;
    map_s.j = 0;

    if (!game || !game->map)
    {
        printf("Error: game or game->map is NULL\n");
        return (map_s);
    }

    map = game->map;
    prev = 0;

    while (map[map_s.i])
    {
        if (map[map_s.i][0] == '\0')
        {
            print_error("Error : empty line found\n");
			free_game(game);
			exit(1);
        }

        map_s.j = 0;
        while (map[map_s.i][map_s.j])
            map_s.j++;

        printf("map[%d] length = %d\n", map_s.i, map_s.j);

        if (prev == 0)
            prev = map_s.j;
        else if (prev != map_s.j)
        {
            printf("Error: map lines have different lengths\n");
            map_s.i = -1;
            map_s.j = -1;
            return (map_s);
        }

        map_s.i++;
    }
    return (map_s);
}

void	check_width_and_height(t_game *game, t_map	size_map)
{
	int	width;
	int	height;

	width = size_map->j;
	height = size_map->i;
	if ((width * 32 > 3200) || (width * 32 == 0))
	{
		print_error("Error : map is so long\n");
		free_game(game);
		exit(1);
	}
	if ((height * 32 > 1720) || (height * 32 == 0))
	{
		print_error("Error : map is so long\n");
		free_game(game);
		exit(1);
	}
}

void	add_one(t_valid *sume, char c)
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

void	get_number(t_valid *sume, char **map)
{
	int	i;
	int	j;

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

void	validate_component_map(t_game	*game)
{
	t_valid	*sume;

	sume = (t_valid *)malloc(sizeof(t_valid));
	if (!sume)
	{
		print_error("Memory allocation failed!\n");
		free_game(game);
		exit(1);
	}
	sume->wall = 0;
	sume->space = 0;
	sume->exit = 0;
	sume->player = 0;
	sume->collectibl = 0;
	get_number(sume, game->map);
	if (sume->wall < 1 || sume->player != 1 || sume->collectibl < 1
		|| sume->exit != 1 || sume->space < 1)
	{
		print_error("Error: Invalid component in map!\n");
		free(sume);
		free_game(game);
		exit(1);
	}
	free(sume);
}
