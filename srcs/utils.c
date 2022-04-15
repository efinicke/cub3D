/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:33:05 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 12:29:26 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	failure(const char *s)
{
	if (s)
	{
		ft_putstr_fd("Error\n", STDERR);
		if (errno)
			perror(s);
		else
		{
			ft_putstr_fd(s, STDERR);
			ft_putstr_fd("\n", STDERR);
		}
	}
	return (-1);
}

int	map_has_wall_at(t_cub *cub, char **map, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > (cub->map_width - 1) || y < 0 || y > (cub->map_height - 1))
		return (TRUE);
	map_x = floor(x);
	map_y = floor(y);
	return (map[map_y][map_x] != '0' \
	&& map[map_y][map_x] != 'N' && map[map_y][map_x] != 'S' \
	&& map[map_y][map_x] != 'E' && map[map_y][map_x] != 'W');
}
