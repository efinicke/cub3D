/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:17:15 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:07:04 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Set the pixel (color) at position [x, y] of the image.                     */

void	img_set_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return ;
	*(int *) \
	(img->addr + (y * img->line_length + x * img->pixel_length)) = color;
}

/* Get the pixel (color) at position [x, y] of the image.                     */

int	img_get_pixel(t_img *img, int x, int y)
{
	return (*(int *) \
	(img->addr + (y * img->line_length + x * (img->pixel_length))));
}

/* Set all pixels of the image to the given color                             */

void	img_fill(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			img_set_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
