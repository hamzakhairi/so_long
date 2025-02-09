/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:46:13 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/09 20:48:47 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	size_map(char	**map)
{
	t_map	map_s;
	int		prev;

	map_s.i = 0;
	map_s.j = 0;
	prev = 0;
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
	return (map_s);
}

void	valid_first_wall_and_last_wall(char **map, int i, int j)
{
	while (map[i][j])
	{
		if (map[i][j] != '1')
		{
			printf("Invalid wall at row %d, column %d\n", i, j);
			free_map(map);
			exit(1);
		}
		j++;
	}
}

void	valid_midell_wall(char **map, int i, int j, int size_j)
{
	while (map[i][j])
	{
		if ((j == 0 || j == size_j - 1) && map[i][j] != '1')
		{
			printf("Invalid wall at row %d, column %d\n", i, j);
			free_map(map);
			exit(1);
		}
		j++;
	}
}

void	validate_wall(char	**map)
{
	t_map	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = size_map(map);
	while (map[i])
	{
		j = 0;
		if (i == 0 || i == size.i - 1)
			valid_first_wall_and_last_wall(map, i, j);
		else
			valid_midell_wall(map, i, j, size.j);
		i++;
	}
}

void	valide(char	**map)
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
			if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] != 'E')
				&& (map[i][j] != 'P') && (map[i][j] != 'C'))
			{
				printf("[1] Bad character in map %d %d %c\n", i, j, map[i][j]);
				free_map(map);
				exit(1);
			}
			j++;
		}
		i++;
	}
	validate_wall(map);
    validate_map(map);
}
