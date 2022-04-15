/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 03:16:53 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_map_width(t_cub *cub, char **map)
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	len;

	if (!(map) || !(map[0]))
		return (-1);
	height = 1;
	width = ft_strlen(map[0]);
	while (map[height])
	{
		len = ft_strlen(map[height]);
		if (width < len)
			width = len;
		height++;
	}
	if (height < 3)
		return (-1);
	cub->map_width = width;
	cub->map_height = height;
	return (width);
}

static int	normalize_lines_length(char **map, int size)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		ptr = map[i];
		map[i] = malloc(sizeof(char) * (size + 1));
		if (!(map[i]))
		{
			map[i] = ptr;
			return (failure("Malloc failure"));
		}
		j = -1;
		while (ptr[++j])
			map[i][j] = ptr[j];
		while (j < size)
			map[i][j++] = ' ';
		map[i][j] = '\0';
		free(ptr);
	}
	return (0);
}

int	normalize_map(t_cub *cub, char **map)
{
	int	size;

	if (!(map))
		return (failure("Missing map content"));
	size = get_map_width(cub, map);
	if (size < 0)
		return (failure("The map content is too small "));
	if (normalize_lines_length(map, size) < 0)
		return (-1);
	return (0);
}
