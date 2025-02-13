/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:57:47 by hkhairi           #+#    #+#             */
/*   Updated: 2024/11/23 14:48:13 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*get_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	count_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	count_bytes = 1;
	while (!ft_strchr(line, '\n') && count_bytes > 0)
	{
		count_bytes = read(fd, buffer, BUFFER_SIZE);
		if (count_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[count_bytes] = '\0';
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

t_gnl	get_and_update_line(char *line)
{
	t_gnl	str;

	str.return_line = extract_first_line(line);
	str.new_line = update_remaining_line(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	t_gnl		str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = get_line(fd, line);
	if (!line)
		return (NULL);
	str = get_and_update_line(line);
	line = str.new_line;
	return (str.return_line);
}
