/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:10:49 by hkhairi           #+#    #+#             */
/*   Updated: 2024/11/22 10:44:37 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *line, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!line)
		line = ft_strdup("");
	if (!line || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(line) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (line)
		while (line[++i] != '\0')
			str[i] = line[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(line) + ft_strlen(buff)] = '\0';
	free(line);
	return (str);
}

char	*extract_first_line(const char *line)
{
	char	*first_line;
	int		count;
	int		i;

	if (!line[0])
		return (NULL);
	count = 0;
	while (line[count] && line[count] != '\n')
		count++;
	first_line = (char *)malloc(sizeof(char) * (count + 2));
	if (!first_line)
		return (NULL);
	i = 0;
	while (i < count)
	{
		first_line[i] = line[i];
		i++;
	}
	if (line[count] == '\n')
		first_line[count++] = '\n';
	first_line[count] = '\0';
	return (first_line);
}

char	*update_remaining_line(char *line)
{
	char	*remaining_line;
	int		count;
	int		i;

	count = 0;
	while (line[count] && line[count] != '\n')
		count++;
	if (line[count] == '\0')
	{
		free(line);
		return (NULL);
	}
	remaining_line = (char *)malloc(sizeof(char) * (ft_strlen(line) - count));
	if (!remaining_line)
		return (NULL);
	count++;
	i = 0;
	while (line[count])
		remaining_line[i++] = line[count++];
	remaining_line[i] = '\0';
	free(line);
	return (remaining_line);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
