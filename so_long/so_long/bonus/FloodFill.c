/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FloodFill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:45:07 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/12 13:32:23 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	find_player(char **map)
{
	t_point	player;
	int		i;
	int		j;

	player.x = -1;
	player.y = -1;
	i = 0;
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

char	**copy_map(char **map, int rows)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup_str(map[i]);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'M')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	erro_copy_map(t_game *game, char **map_copy)
{
	printf("Invalid map\n");
	free_map(map_copy);
	free_game(game);
	exit(1);
}

void	validate_map(t_game *game)
{
	t_point	player;
	char	**map_copy;
	t_map	size;
	char **map;

	map = game->map;
	player = find_player(map);
	cheack_player(player.x, player.y, game);
	size = size_map(game);
	map_copy = copy_map(map, size.i);
	if (!map_copy)
	{
		printf("Error: Failed to copy the map.\n");
		free_game(game);
		exit(1);
	}
	flood_fill(map_copy, player.x, player.y);
	if (!check_copy_map(map_copy, size.i))
		erro_copy_map(game, map_copy);
	free_map(map_copy);
}
