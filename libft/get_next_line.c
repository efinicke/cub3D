/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:39:06 by spayeur           #+#    #+#             */
/*   Updated: 2021/11/20 10:08:50 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_line_malloc(char **line, char *buffer)
{
	*line = malloc(sizeof(char) * 1);
	if (!(*line))
		return (ft_mallocprotect(NULL, &buffer, -1));
	*line[0] = '\0';
	return (0);
}

static char	*ft_buffer_malloc(char **line, char *buffer, int *ret)
{
	*ret = 0;
	if (buffer)
	{
		*ret = ft_strlcatbuffermanager(line, buffer, 8);
		if ((ret) != 0)
			return (buffer);
	}
	if (!(buffer))
	{
		buffer = malloc(sizeof(char) * 8 + 1);
		if (!(buffer))
		{
			ft_mallocprotect(line, NULL, -1);
			return (NULL);
		}
	}
	return (buffer);
}

static int	check_param_and_malloc_line(int fd, char **line, char *buffer)
{
	if (fd < 0 || 8 < 1 || read(fd, buffer, 0) == -1 || !line)
		return (-1);
	if (ft_line_malloc(line, buffer) == -1)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line, int stop)
{
	static char		*buffer = NULL;
	unsigned int	size;
	int				ret;

	if (stop)
		return (ft_mallocprotect(NULL, &buffer, 0));
	if (check_param_and_malloc_line(fd, line, buffer) == -1)
		return (-1);
	buffer = ft_buffer_malloc(line, buffer, &ret);
	if ((ret) != 0)
		return (ret);
	if (!(buffer))
		return (ft_mallocprotect(line, NULL, -1));
	buffer[8] = '\0';
	size = read(fd, buffer, 8);
	while ((size) > 0)
	{
		ret = ft_strlcatbuffermanager(line, buffer, size);
		if ((ret) != 0)
			return (ret);
		size = read(fd, buffer, 8);
	}
	if (!(size))
		return (ft_mallocprotect(NULL, &buffer, 0));
	return (1);
}
