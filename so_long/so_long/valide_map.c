/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:46:13 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/10 16:15:19 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	size_map(t_game *game)
{
	t_map	map_s;
	int		prev;
	char **map;

	map = game->map;
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
			free_game(game);
			exit(1);
		}
		map_s.i++;
	}
	return (map_s);
}

void	valid_first_wall_and_last_wall(t_game *game, int i, int j)
{
	char **map;

	map = game->map;
	while (map[i][j])
	{
		if (map[i][j] != '1')
		{
			printf("Invalid wall at row %d, column %d\n", i, j);
			free_game(game);
			exit(1);
		}
		j++;
	}
}

void	valid_midell_wall(t_game *game, int i, int j, int size_j)
{
	char **map;

	map = game->map;
	while (map[i][j])
	{
		if ((j == 0 || j == size_j - 1) && map[i][j] != '1')
		{
			printf("Invalid wall at row %d, column %d\n", i, j);
			free_game(game);
			exit(1);
		}
		j++;
	}
}

void	validate_wall(t_game *game)
{
	t_map	size;
	int		i;
	int		j;
	char **map;

	i = 0;
	j = 0;
	map = game->map;
	size = size_map(game);
	while (map[i])
	{
		j = 0;
		if (i == 0 || i == size.i - 1)
			valid_first_wall_and_last_wall(game, i, j);
		else
			valid_midell_wall(game, i, j, size.j);
		i++;
	}
}

void	valide(t_game *game)
{
	int	i;
	int	j;
	char **map;

	i = 0;
	j = 0;
	map = game->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] != 'E')
				&& (map[i][j] != 'P') && (map[i][j] != 'C'))
			{
				printf("[1] Bad character in map %d %d %c\n", i, j, map[i][j]);
				free_game(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
	validate_wall(game);
	validate_map(game);
}
