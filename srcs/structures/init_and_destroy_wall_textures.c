/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_destroy_wall_textures.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:58:36 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/13 17:04:27 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_xpm_file(t_img *img)
{
	img->addr = (unsigned int *)mlx_get_data_addr(img->ptr, \
		&img->bits_per_pixel, \
	&img->line_length, &img->endian);
	img->pixel_length = img->bits_per_pixel / 8;
}

int	init_textures(t_cub *cub)
{
	cub->texture.south.ptr = mlx_xpm_file_to_image(cub->mlx, \
		cub->so, \
		&cub->texture.south.width, &cub->texture.south.height);
	if (!(cub->texture.south.ptr))
		return (failure("Unable to create the north texture"));
	fill_xpm_file(&cub->texture.south);
	cub->texture.east.ptr = mlx_xpm_file_to_image(cub->mlx, \
		cub->ea, \
		&cub->texture.east.width, &cub->texture.east.height);
	if (!(cub->texture.east.ptr))
		return (failure("Unable to create the north texture"));
	fill_xpm_file(&cub->texture.east);
	cub->texture.west.ptr = mlx_xpm_file_to_image(cub->mlx, \
		cub->we, \
		&cub->texture.west.width, &cub->texture.west.height);
	if (!(cub->texture.west.ptr))
		return (failure("Unable to create the north texture"));
	fill_xpm_file(&cub->texture.west);
	cub->texture.north.ptr = mlx_xpm_file_to_image(cub->mlx, \
		cub->no, \
		&cub->texture.north.width, &cub->texture.north.height);
	if (!(cub->texture.north.ptr))
		return (failure("Unable to create the north texture"));
	fill_xpm_file(&cub->texture.north);
	return (0);
}

void	destroy_textures(t_cub *cub)
{
	if (cub->texture.south.ptr != NULL)
		mlx_destroy_image(cub->mlx, cub->texture.south.ptr);
	if (cub->texture.north.ptr != NULL)
		mlx_destroy_image(cub->mlx, cub->texture.north.ptr);
	if (cub->texture.east.ptr != NULL)
		mlx_destroy_image(cub->mlx, cub->texture.east.ptr);
	if (cub->texture.west.ptr != NULL)
		mlx_destroy_image(cub->mlx, cub->texture.west.ptr);
}
