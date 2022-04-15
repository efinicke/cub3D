/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_wall_projection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:20 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/13 17:18:02 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_width_offset(int x, t_cub *cub, int *offset_x, t_img *texture)
{
	if (cub->rays[x].was_hit_vertical)
		*offset_x = (cub->rays[x].wall_hit_y - floor(cub->rays[x].wall_hit_y)) \
		* (texture->width);
	else
		*offset_x = (cub->rays[x].wall_hit_x - floor(cub->rays[x].wall_hit_x)) \
		* (texture->width);
}

static void	get_height_offset(int y, t_cub *cub, int *offset_y, t_img *texture)
{
	int	dist_from_top;

	dist_from_top = y + (cub->plane.wall_strip_height / 2) \
	- (WINDOW_HEIGHT / 2);
	*offset_y = \
	dist_from_top * ((float)texture->height / cub->plane.wall_strip_height);
}

static t_img	*define_wall_texture(int x, t_cub *cub)
{
	t_img	*texture;

	texture = NULL;
	if (cub->rays[x].was_hit_vertical \
	&& cub->rays[x].is_facing_right)
		texture = &cub->texture.west;
	else if (cub->rays[x].was_hit_vertical \
	&& cub->rays[x].is_facing_left)
		texture = &cub->texture.east;
	else if ((cub->rays[x].was_hit_vertical == 0) \
	&& cub->rays[x].is_facing_up)
		texture = &cub->texture.south;
	else if ((cub->rays[x].was_hit_vertical == 0) \
	&& cub->rays[x].is_facing_down)
		texture = &cub->texture.north;
	return (texture);
}

void	set_wall_stripe(int x, t_cub *cub, t_img *background, t_img *texture)
{
	int				y;
	int				offset_y;
	int				offset_x;
	unsigned int	color;

	offset_x = 0;
	offset_y = 0;
	y = cub->plane.top_wall_pixel;
	texture = define_wall_texture(x, cub);
	get_width_offset(x, cub, &offset_x, texture);
	while (y < cub->plane.bot_wall_pixel)
	{
		get_height_offset(y, cub, &offset_y, texture);
		color = img_get_pixel(texture, offset_x, offset_y);
		img_set_pixel(background, x, y, color);
		y++;
	}
}
