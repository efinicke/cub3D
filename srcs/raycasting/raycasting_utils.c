/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:32 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/12 02:09:32 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Get the next point to check. Based on the point of the next touch and      */
/* adjusting according to the orientation.                                    */

static void	get_next_point_to_check(const t_ray *ray, t_fpoint *next_touch, \
		t_fpoint *to_check, int horizontal_search)
{
	if (horizontal_search)
	{
		to_check->x = next_touch->x;
		to_check->y = next_touch->y - ray->is_facing_up;
	}
	else
	{
		to_check->x = next_touch->x - ray->is_facing_left;
		to_check->y = next_touch->y;
	}
}

/* Increment next_touch by step                                               */

static void	increment_next_touch(t_fpoint *next_touch, t_fpoint *step)
{
	next_touch->x += step->x;
	next_touch->y += step->y;
}

/* Find the first wall encountered by the ray.                                */
/* For more details on the points see the comments on the functions below.    */
/* pts[0] --> next_touch                                                      */
/* pts[1] --> to_check                                                        */
/* pts[2] --> step                                                            */

static void	search_wall_hit(t_cub *cub, int id, t_fpoint pts[3], \
			int horizontal_search)
{
	float	distance;

	while (0 <= pts[0].x && pts[0].x <= cub->map_width \
		&& 0 <= pts[0].y && pts[0].y <= cub->map_height)
	{
		get_next_point_to_check(&cub->rays[id], &pts[0], &pts[1], \
		horizontal_search);
		if (map_has_wall_at(cub, cub->map, pts[1].x, pts[1].y))
		{
			distance = distance_between_points(cub->player.x, cub->player.y, \
			pts[0].x, pts[0].y);
			if (cub->rays[id].distance > 0 && cub->rays[id].distance < distance)
				break ;
			cub->rays[id].wall_hit_x = pts[0].x;
			cub->rays[id].wall_hit_y = pts[0].y;
			cub->rays[id].distance = distance;
			cub->rays[id].wall_hit_content = \
			cub->map[(int)floor(pts[1].y)][(int)floor(pts[1].x)];
			cub->rays[id].was_hit_vertical = !(horizontal_search);
			break ;
		}
		else
			increment_next_touch(&pts[0], &pts[2]);
	}
}

/* Intialize the points to find vertical wall hits then call the              */
/* search_wall_hit() function.                                                */
/* next_touch represents the next point that will be touched by the ray.      */
/* to_check represents the point to check. This point is based on next_touch  */
/* and is more accurate since it fits the player's orientation.               */
/* step is not a point. It represents the step in x and y between a touch and */
/* the next touch. It increments next_touch.                                  */

void	search_horizontal_wall_hit(t_cub *cub, int id)
{
	t_fpoint	next_touch;
	t_fpoint	to_check;
	t_fpoint	step;
	t_fpoint	*pts[3];

	pts[0] = &next_touch;
	pts[1] = &to_check;
	pts[2] = &step;
	next_touch.y = floor(cub->player.y);
	next_touch.y += cub->rays[id].is_facing_down;
	next_touch.x = cub->player.x + (next_touch.y - cub->player.y) \
	/ tan(cub->rays[id].angle);
	to_check.y = next_touch.y - cub->rays[id].is_facing_up;
	to_check.x = next_touch.x;
	step.y = 1;
	step.x = 1 / tan(cub->rays[id].angle);
	if (cub->rays[id].is_facing_up)
		step.y *= -1;
	if ((cub->rays[id].is_facing_left && step.x > 0) \
	|| (cub->rays[id].is_facing_right && step.x < 0))
		step.x *= -1;
	search_wall_hit(cub, id, *pts, TRUE);
}

/* Intialize the points to find vertical wall hits then call the              */
/* search_wall_hit() function.                                                */
/* next_touch represents the next point that will be touched by the ray.      */
/* to_check represents the point to check. This point is based on next_touch  */
/* and is more accurate since it fits the player's orientation.               */
/* step is not a point. It represents the step in x and y between a touch and */
/* the next touch. It increments next_touch.                                  */

void	search_vertical_wall_hit(t_cub *cub, int id)
{
	t_fpoint	next_touch;
	t_fpoint	to_check;
	t_fpoint	step;
	t_fpoint	*pts[3];

	pts[0] = &next_touch;
	pts[1] = &to_check;
	pts[2] = &step;
	next_touch.x = floor(cub->player.x);
	next_touch.x += cub->rays[id].is_facing_right;
	next_touch.y = cub->player.y + (next_touch.x - cub->player.x) \
	* tan(cub->rays[id].angle);
	to_check.x = next_touch.x - cub->rays[id].is_facing_left;
	to_check.y = next_touch.y;
	step.x = 1;
	step.y = 1 * tan(cub->rays[id].angle);
	if (cub->rays[id].is_facing_left)
		step.x *= -1;
	if ((cub->rays[id].is_facing_up && step.y > 0) \
	|| (cub->rays[id].is_facing_down && step.y < 0))
		step.y *= -1;
	search_wall_hit(cub, id, *pts, FALSE);
}
