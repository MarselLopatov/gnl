/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:46:11 by cdoria            #+#    #+#             */
/*   Updated: 2021/10/27 21:36:38 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>	// удалить

char	*ft_clear(t_list *head, char **buf, char **line, int kostil)
{
	if ((**line == 0 && kostil == 1) || (*line == 0 && kostil == 1))
	{
		free (*line);
		*line = NULL;
	}
	if (buf && *buf)
		free (*buf);
	if (head->cache)
	{
		free (head->cache);
		head->cache = NULL;
	}
	if (*line == NULL && head != NULL && kostil == 1)// я фришу каждый раз head  и он никогда не станет NULL
	{
		free (head);
	}
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

int	check_cache(t_list **head, char **line, char **buf)
{
	char	*point_n;

	if ((*head)->cache != NULL)
	{
		point_n = ft_strchr((*head)->cache, '\n');
		if (point_n)
		{
			//*point_n = '\0';
			*line = ft_strdup((*head)->cache);
			point_n = ft_save_cache(++point_n);

		//head->cache = ft_save_cache(++point_n);
			
			ft_clear(*head, buf, line, 0);
			(*head)->cache = point_n;
			//point_n = ft_strjoin (head->cache, ++point_n); // тут же я приклеиваю 2 строки
			//ft_clear(head, buf, line, 0);
			//head->cache = point_n;
			//free (*buf);
			return (1);
		}
		else
		{
			*line = ft_strdup ((*head)->cache);
			free ((*head)->cache);
			(*head)->cache = NULL;
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

char	*get_line(t_list **head, char **buf, char **line)
{
	int		rd;
	char	*point_n;
	//char	*tmp;

	while (1)
	{
		rd = read ((*head)->fd, *buf, BUFFER_SIZE);
		if (rd <= 0 && (*head)->cache == NULL)
			return (ft_clear(*head, buf, line, 1)); // нужно разобраться
		(*buf)[rd] = '\0';
		point_n = ft_strchr(*buf, '\n');
		if (point_n)
		{
			*line = ft_strjoin (*line, *buf); // мб з десь утечка при фришке
			point_n = ft_save_cache(++point_n);

			ft_clear(*head, buf, line, 0);
		// функцию которая запоминает весь кэш

			(*head)->cache = point_n;
		//head->cache = ft_save_cache(++point_n);
			//head->cache = ft_strdup (++point_n); // strdup ??????????????????????
			//ft_strcpy (head->cache, ++point_n);
		//free (*buf);				// мб так же здесь
			return (*line);
		}
		else
		{
			//tmp = *line;
			*line = ft_strjoin (*line, *buf);
			//free (tmp);
			//return (*line);
		}
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
		temp->next = ft_newlist(fd);
	// проверка на кеш	УБЕРИ КОМЕНТЫ ГНИДА 
	if (check_cache(&temp, &line, &buf))
		return (line);
	line = get_line(&temp, &buf, &line);
	//free (buf);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int		fd;
	int		fd1;
	char	*line;
	char	*line1;

	fd1 = open("test1", O_RDONLY);
	fd = open("test", O_RDONLY);
	line = get_next_line(fd);
	line = get_next_line(fd);
	line = get_next_line(fd);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
}

//0x116ada5c0