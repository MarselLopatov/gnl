/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:28:53 by coleta            #+#    #+#             */
/*   Updated: 2021/12/05 17:23:03 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len1;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	join = (char *)malloc (sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	join = ft_strlcat(s1, s2, len1, join);
	free (s1);
	return (join);
}

char	*ft_strlcat(char *s1, char *s2, int len1, char *join)
{
	int		i;

	i = 0;
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
	return (join);
}
