/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:32 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/13 14:45:16 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

static void	init_ray(t_ray *ray)
{
	ray->angle = -1.0f;
	ray->wall_hit_x = -1.0f;
	ray->wall_hit_y = -1.0f;
	ray->distance = -1.0f;
	ray->was_hit_vertical = -1;
	ray->is_facing_up = -1;
	ray->is_facing_down = -1;
	ray->is_facing_left = -1;
	ray->is_facing_right = -1;
	ray->wall_hit_content = '\0';
}

static void	cast_ray(t_cub *cub, float angle, int id)
{
	angle = normalize_angle(angle);
	init_ray(&cub->rays[id]);
	cub->rays[id].angle = angle;
	cub->rays[id].is_facing_down = (angle > ZERO_PI && angle < PI);
	cub->rays[id].is_facing_up = !(cub->rays[id].is_facing_down);
	cub->rays[id].is_facing_right = (angle < HALF_PI || angle > THREE_PI_TWO);
	cub->rays[id].is_facing_left = !(cub->rays[id].is_facing_right);
	search_horizontal_wall_hit(cub, id);
	search_vertical_wall_hit(cub, id);
}

void	cast_all_rays(t_cub *cub)
{
	float			angle;
	unsigned int	i;

	i = 0;
	angle = cub->player.rotation_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		cast_ray(cub, angle, i);
		angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
