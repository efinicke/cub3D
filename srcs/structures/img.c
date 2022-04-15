/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:08:39 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 04:51:50 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_img(t_cub *cub, t_img *img, int width, int height)
{
	img->ptr = mlx_new_image(cub->mlx, width, height);
	if (!(img->ptr))
		return (-1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	img->pixel_length = img->bits_per_pixel / 8;
	img->width = width;
	img->height = height;
	return (0);
}
