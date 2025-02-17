/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:05:00 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 14:39:39 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	number_map(char	*file)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	close(fd);
	return (i);
}

static int	ft_len_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_str(char	*src)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = ft_len_str(src);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		if (src[i] != '\n')
			dup[i] = src[i];
		else
			break ;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	fill_map(int fd, char **map)
{
	int		i;
	char	*str;

	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		map[i] = ft_strdup_str(str);
		free(str);
		if (!map[i] || map[i][0] == '\0')
		{
			print_error("Error : Invalid map (last line is empty)\n");
			free_map(map);
			exit(1);
		}
		str = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
}

char	**read_map(char	*file)
{
	int		fd;
	int		number;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error("Error : opening file\n");
		return (NULL);
	}
	number = number_map(file);
	if (number <= 0)
	{
		close(fd);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (number + 1));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	fill_map(fd, map);
	close(fd);
	return (map);
}
