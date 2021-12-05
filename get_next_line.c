/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:46:11 by cdoria            #+#    #+#             */
/*   Updated: 2021/12/05 17:22:29 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clear(char **cache, char **buf, char **line, int kostil)
{
	if ((**line == 0 && kostil == 1) || (*line == 0 && kostil == 1))
	{
		free (*line);
		*line = NULL;
	}
	if (buf && *buf)
		free (*buf);
	if (*cache)
	{
		free (*cache);
		*cache = NULL;
	}
	return (*line);
}

char	*ft_save_cache(char *point_n)
{
	char	*str;
	int		i;

	if (!*point_n)
		return (NULL);
	str = malloc (sizeof(char) * (ft_strlen(point_n) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (point_n[i])
	{
		str[i] = point_n[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	check_cache(char **cache, char **line, char **buf)
{
	char	*point_n;

	if (*cache != NULL)
	{
		point_n = ft_strchr(*cache, '\n');
		if (point_n)
		{
			*line = ft_strdup(*cache);
			point_n = ft_save_cache(++point_n);
			ft_clear(cache, buf, line, 0);
			*cache = point_n;
			return (1);
		}
		else
		{
			*line = ft_strdup (*cache);
			free (*cache);
			*cache = NULL;
			return (0);
		}
	}
	*line = malloc(1);
	**line = 0;
	return (0);
}

char	*get_line(char **cache, char **buf, char **line, int fd)
{
	int		rd;
	char	*point_n;

	while (1)
	{
		rd = read (fd, *buf, BUFFER_SIZE);
		if (rd <= 0 && *cache == NULL)
			return (ft_clear(cache, buf, line, 1));
		(*buf)[rd] = '\0';
		point_n = ft_strchr(*buf, '\n');
		if (point_n)
		{
			*line = ft_strjoin (*line, *buf);
			point_n = ft_save_cache(++point_n);
			ft_clear(cache, buf, line, 0);
			*cache = point_n;
			return (*line);
		}
		else
			*line = ft_strjoin (*line, *buf);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (check_cache(&cache, &line, &buf))
		return (line);
	line = get_line(&cache, &buf, &line, fd);
	return (line);
}
