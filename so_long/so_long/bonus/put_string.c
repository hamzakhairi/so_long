/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:04:03 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 18:07:06 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_char(char c)
{
	write(1, &c, 1);
}

void	put_nbr(int nbr)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		put_char('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		put_nbr(nbr / 10);
		put_nbr(nbr % 10);
	}
	else
		put_char(nbr + '0');
}

void	print_error(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
