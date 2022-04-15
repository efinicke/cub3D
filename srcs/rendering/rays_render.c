/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:32 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/12 03:42:05 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ray_render(t_cub *cub, const t_ray *ray, \
			int center_x, int center_y)
{
	t_img			direction;
	t_ipoint		a;
	t_ipoint		b;
	t_ipoint		pos;
	t_ipoint		*pts[3];

	pts[0] = &a;
	pts[1] = &b;
	pts[2] = &pos;
	init_point(&a, 0, 0);
	init_point(&b, cos(ray->angle) * ray->distance * MINITILE_SIZE, \
	sin(ray->angle) * ray->distance * MINITILE_SIZE);
	if (a.x <= b.x && a.y <= b.y)
		init_point(&pos, a.x, a.y);
	else if (a.x >= b.x && a.y >= b.y)
		init_point(&pos, b.x, b.y);
	else if (a.x <= b.x && a.y >= b.y)
		init_point(&pos, a.x, b.y);
	else if (a.x >= b.x && a.y <= b.y)
		init_point(&pos, b.x, a.y);
	if (draw_line(cub, &direction, pts, RAYS_COLOR) < 0)
		return ;
	put_img_to_minimap(cub, &direction, pos.x + center_x, pos.y + center_y);
	mlx_destroy_image(cub->mlx, direction.ptr);
}

void	rays_render(t_cub *cub)
{
	int	i;	

	if (!(RENDER_RAYS))
		return ;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_render(cub, &cub->rays[i], cub->minimap.width / 2, \
		cub->minimap.height / 2);
		i++;
	}
	put_img_to_background(cub, &cub->minimap.frame, MINIMAP_X, MINIMAP_Y);
}
