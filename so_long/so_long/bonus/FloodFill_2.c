/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FloodFill_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:36:15 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 14:34:53 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_copy_map(char **map, int row)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < row)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E' || map[i][j] == 'C')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	cheack_player(int x, int y, t_game *game)
{
	if (x == -1 && y == -1)
	{
		print_error("Error: Player not found in the map.\n");
		free_game(game);
		exit(1);
	}
}
