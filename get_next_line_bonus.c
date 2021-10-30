/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsel <marsel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:46:11 by cdoria            #+#    #+#             */
/*   Updated: 2021/10/30 13:56:37 by marsel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>	// удалить

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
	// if (*line == NULL && kostil == 1)// я фришу каждый раз head  и он никогда не станет NULL
	// 	free (head);
	return (*line);
}

t_list	*ft_newlist(int fd)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->cache = NULL;
	new->next = NULL;
	return (new);
}

int	check_cache(char **cache, char **line, char **buf)
{
	char	*point_n;

	if (*cache != NULL)
	{
		point_n = ft_strchr(*cache, '\n');
		if (point_n)
		{
			//*point_n = '\0';
			*line = ft_strdup(*cache);
			point_n = ft_save_cache(++point_n);

		//head->cache = ft_save_cache(++point_n);
			
			ft_clear(cache, buf, line, 0);
			*cache = point_n;
			//point_n = ft_strjoin (head->cache, ++point_n); // тут же я приклеиваю 2 строки
			//ft_clear(head, buf, line, 0);
			//head->cache = point_n;
			//free (*buf);
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
	else
	{
		*line = malloc(1);
		**line = 0;
	}
	return (0);
}

char	*get_line(char **cache, char **buf, char **line, int fd)
{
	int		rd;
	char	*point_n;
	//char	*tmp;

	while (1)
	{
		rd = read (fd, *buf, BUFFER_SIZE);
		if (rd <= 0 && *cache == NULL)
			return (ft_clear(cache, buf, line, 1)); // нужно разобраться
		(*buf)[rd] = '\0';
		point_n = ft_strchr(*buf, '\n');
		if (point_n)
		{
			*line = ft_strjoin (*line, *buf); // мб з десь утечка при фришке
			point_n = ft_save_cache(++point_n);

			ft_clear(cache, buf, line, 0);
		// функцию которая запоминает весь кэш

			*cache = point_n;
		//head->cache = ft_save_cache(++point_n);
			//head->cache = ft_strdup (++point_n); // strdup ??????????????????????
			//ft_strcpy (head->cache, ++point_n);
		//free (*buf);				// мб так же здесь
			return (*line);
		}
		else
			*line = ft_strjoin (*line, *buf);
	}
	return (*line); // мб возвращать 0
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*line;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (!head)
		head = ft_newlist(fd);
	temp = head;
	while (temp->next && temp->fd != fd)
		temp = temp->next;
	if (temp->fd != fd)
	{
		temp->next = ft_newlist(fd);
		temp = temp->next;
	}
	// проверка на кеш	УБЕРИ КОМЕНТЫ ГНИДА 
	if (check_cache(&temp->cache, &line, &buf))
		return (line);
	line = get_line(&temp->cache, &buf, &line, temp->fd);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int		fd;
// 	int		fd1;
// 	char	*line;
// 	char	*line1;

// 	fd = open("test", O_RDONLY);
// 	fd1 = open("test1", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("0: %s", line);
// 	line = get_next_line(fd);
// 	printf("0: %s", line);
// 	line1 = get_next_line(fd1);
// 	printf("1: %s", line1);
// 	line = get_next_line(fd);
// 	printf("0: %s", line);
// 	line1 = get_next_line(fd1);
// 	printf("1: %s", line1);
// 	// while (line = get_next_line(fd))
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// }

//0x116ada5c0