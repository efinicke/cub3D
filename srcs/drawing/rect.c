/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:03:08 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/08 02:14:11 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	draw_rect_unfilled(t_cub *cub, t_img *img, const int wh[2], int color)
{
	int	y_ptr;
	int	x_ptr;

	if (wh[0] <= 0 || wh[1] <= 0)
		return (-1);
	if (init_img(cub, img, wh[0], wh[1]) < 0)
		return (-1);
	img_fill(img, 0xff000000);
	y_ptr = 0;
	while (y_ptr <= wh[1])
	{
		x_ptr = 0;
		while (x_ptr <= wh[0])
		{
			if (y_ptr == 0 || y_ptr == (wh[1] - 1) \
			|| x_ptr == 0 || x_ptr == (wh[0] - 1))
				img_set_pixel(img, x_ptr, y_ptr, color);
			x_ptr++;
		}
		y_ptr++;
	}
	return (0);
}

int	draw_rect(t_cub *cub, t_img *img, const int wh[2], int color)
{
	if (wh[0] <= 0 || wh[1] <= 0)
		return (-1);
	if (init_img(cub, img, wh[0], wh[1]) < 0)
		return (-1);
	img_fill(img, color);
	return (0);
}
