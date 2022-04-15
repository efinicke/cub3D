/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:25 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/13 15:25:37 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_ceiling_stripe(int x, t_cub *cub, t_img *background)
{
	int	y;

	y = 0;
	while (y < cub->plane.top_wall_pixel)
	{
		img_set_pixel(background, x, y, cub->c);
		y++;
	}
}

static void	set_floor_stripe(int x, t_cub *cub, t_img *background)
{
	int	y;

	y = cub->plane.bot_wall_pixel;
	while (y < WINDOW_HEIGHT)
	{
		img_set_pixel(background, x, y, cub->f);
		y++;
	}
}

static void	set_plane_values(t_cub *cub, int x)
{
	cub->plane.distance_projection = \
		(WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	cub->plane.perp_distance = \
		cub->rays[x].distance * \
		cos(cub->rays[x].angle - cub->player.rotation_angle);
	cub->plane.projected_wall_height = \
		((1 / cub->plane.perp_distance) * cub->plane.distance_projection);
	cub->plane.wall_strip_height = (int)cub->plane.projected_wall_height;
	cub->plane.top_wall_pixel = \
		(WINDOW_HEIGHT / 2) - (cub->plane.wall_strip_height / 2);
	if (cub->plane.top_wall_pixel < 0)
		cub->plane.top_wall_pixel = 0;
	cub->plane.bot_wall_pixel = \
		(WINDOW_HEIGHT / 2) + (cub->plane.wall_strip_height / 2);
	if (cub->plane.bot_wall_pixel > WINDOW_HEIGHT)
		cub->plane.bot_wall_pixel = WINDOW_HEIGHT;
}

void	generate_3d_projection(t_cub *cub, t_img *background, t_img *texture)
{
	int		x;

	x = 0;
	while (x < NUM_RAYS)
	{
		set_plane_values(cub, x);
		set_ceiling_stripe(x, cub, background);
		set_wall_stripe(x, cub, background, texture);
		set_floor_stripe(x, cub, background);
		x++;
	}
}
