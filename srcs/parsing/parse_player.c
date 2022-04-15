/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 05:56:22 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_player(t_cub *cub, char **map, const char *line)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (line[i] \
	&& line[i] != 'N' && line[i] != 'S' \
	&& line[i] != 'E' && line[i] != 'W')
		i++;
	j = 0;
	while (map && map[j])
		j++;
	if (line[i])
	{
		cub->player.x = i + 0.5;
		cub->player.y = j - 1 + 0.5;
		if (line[i] == 'N')
			cub->player.rotation_angle = THREE_PI_TWO;
		else if (line[i] == 'S')
			cub->player.rotation_angle = HALF_PI;
		else if (line[i] == 'E')
			cub->player.rotation_angle = ZERO_PI;
		else if (line[i] == 'W')
			cub->player.rotation_angle = PI;
	}
	return (0);
}
