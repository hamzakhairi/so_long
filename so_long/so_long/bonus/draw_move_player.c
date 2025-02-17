/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_move_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:38:48 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 17:59:25 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	reverse_str(char *str, int len)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i++] = str[j];
		str[j--] = temp;
	}
}

int	int_to_str_helper(int num, char *str)
{
	int	i;

	i = 0;
	while (num)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	return (i);
}

void	int_to_str(int num, char *str)
{
	int		i;
	bool	is_negative;
	int		len;

	i = 0;
	if (num == 0)
		str[i++] = '0';
	else
	{
		is_negative = (num < 0);
		if (is_negative)
			num = -num;
		len = int_to_str_helper(num, str);
		if (is_negative)
			str[len++] = '-';
		reverse_str(str, len);
		i = len;
	}
	str[i] = '\0';
}

void	get_move_string(int moves, char *buffer)
{
	char	prefix[];
	int		i;

	prefix[] = "Moves: ";
	i = 0;
	while (prefix[i])
	{
		buffer[i] = prefix[i];
		i++;
	}
	int_to_str(moves, buffer + i);
}

void	draw_move_counter(t_game *game)
{
	char		move_str[30];
	int			text_color;

	get_move_string(game->moves, move_str);
	text_color = 0xFF0000;
	mlx_string_put(game->mlx, game->win, 10, 10, text_color, move_str);
}
