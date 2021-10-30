/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsel <marsel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:46:41 by cdoria            #+#    #+#             */
/*   Updated: 2021/10/30 13:21:52 by marsel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s) // использовать для строки
{
	char	*str;
	int		i;

	if (!*s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	str = malloc (sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != 0)
		i++;
	return (i);
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

char	*ft_strjoin(char *s1, char *s2) // использовать для строки
{
	char	*join;
	int		len1;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	join = (char *)malloc (sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	//join[len1 + len2] = '\n';
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i] != '\0' && s2[i] != '\n')
	{
		join[len1 + i] = s2[i];
		i++;
	}
	if (s2 && s2[i] == '\n')
	{
		join[len1 + i] = '\n';
		i++;
	}
	join[len1 + i] = '\0';
	//ft_strlcat(join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free (s1);
	return (join);
}
