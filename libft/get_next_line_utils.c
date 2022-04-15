/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:45:57 by spayeur           #+#    #+#             */
/*   Updated: 2021/06/07 09:19:33 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mallocprotect(char **p1, char **p2, int ret)
{
	if (p1 && *p1)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (p2 && *p2)
	{
		free(*p2);
		*p2 = NULL;
	}
	return (ret);
}

static unsigned int	ft_strlen_ui(const char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static long	ft_strlcatbuffer_extend(char *l, char *buffer, \
		unsigned int size, char **sadr)
{
	unsigned int	i;
	unsigned int	j;
	char			*s;

	i = 0;
	while (i < size && buffer[i] && buffer[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (ft_strlen_ui(l) + i + 1));
	if (!(s))
		return (-1);
	j = 0;
	while (l[j])
	{
		s[j] = l[j];
		j++;
	}
	i = 0;
	while (i < size && buffer[i] && buffer[i] != '\n')
	{
		s[j + i] = buffer[i];
		i++;
	}
	s[j + i] = '\0';
	*sadr = s;
	return (i);
}

static int	ft_strlcatbuffer(char **line, char *l, char *buffer, \
		unsigned int size)
{
	long			i;
	unsigned int	j;
	char			*s;

	i = ft_strlcatbuffer_extend(l, buffer, size, &s);
	if (i == -1)
		return (-1);
	if (buffer[i] && buffer[i] == '\n')
	{
		j = 0;
		while (j + i + 1 < size && buffer[i])
		{
			buffer[j] = buffer[j + i + 1];
			j++;
		}
		while (j < size && buffer[i])
			buffer[j++] = '\0';
		free(*line);
		*line = s;
		return (1);
	}
	free(*line);
	*line = s;
	return (0);
}

int	ft_strlcatbuffermanager(char **line, \
		char *buffer, unsigned int size)
{
	int	ret;

	ret = ft_strlcatbuffer(line, *line, buffer, size);
	if (ret == -1)
		return (ft_mallocprotect(line, &buffer, -1));
	if (ret == 1)
		return (1);
	return (0);
}
