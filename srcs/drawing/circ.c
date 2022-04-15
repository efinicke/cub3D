/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:03:08 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/08 02:14:21 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	draw_circ(t_cub *cub, t_img *img, int radius, int color)
{
	int	dx;
	int	dy;
	int	i;
	int	j;

	if (radius < 0)
		return (-1);
	if (init_img(cub, img, (radius * 2), (radius * 2)) < 0)
		return (-1);
	img_fill(img, 0xff000000);
	i = 0;
	while (i < (radius * 2))
	{
		j = 0;
		while (j < (radius * 2))
		{
			dx = radius - i;
			dy = radius - j;
			if ((unsigned int)(dx * dx + dy * dy) <= (radius * radius))
				img_set_pixel(img, radius + dx, radius + dy, color);
			j++;
		}
		i++;
	}
	return (0);
}
