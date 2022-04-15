/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 11:50:33 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_cub_configuration(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->f = -1;
	cub->c = -1;
	cub->map = NULL;
	cub->player.x = -1.0;
	cub->player.y = -1.0;
	cub->player.rotation_angle = -1.0;
}

int	parse_cub_file(t_cub *cub, int fd)
{
	char			*line;
	unsigned int	i;

	init_cub_configuration(cub);
	i = 1;
	while (get_next_line(fd, &line, 0) == 1)
	{
		if (parse_line(cub, line) < 0)
		{
			free(line);
			get_next_line(fd, &line, 1);
			return (-1);
		}
		free(line);
		i++;
	}
	free(line);
	if (check_missing_element(cub) < 0)
		return (-1);
	if (normalize_map(cub, cub->map) < 0)
		return (-1);
	if (check_map(cub->map) < 0)
		return (-1);
	return (0);
}
