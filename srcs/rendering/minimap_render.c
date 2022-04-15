/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:16:57 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:08:10 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	background_render(t_cub *cub)
{
	put_img_to_minimap(cub, &cub->minimap.background, 0, 0);
}

static void	tile_render(t_cub *cub, char **map, int i, int j)
{
	int	x;
	int	y;

	x = ((j - cub->player.x) * MINITILE_SIZE) + ((cub->minimap.width) / 2);
	y = ((i - cub->player.y) * MINITILE_SIZE) + ((cub->minimap.height) / 2);
	if (map[i][j] == ' ')
		put_img_to_minimap(cub, &cub->minimap.tile_void, x, y);
	else if (map[i][j] == '1')
		put_img_to_minimap(cub, &cub->minimap.tile_wall, x, y);
	else
		put_img_to_minimap(cub, &cub->minimap.tile_space, x, y);
}

static void	player_direction_render(t_cub *cub, int center_x, int center_y)
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
	init_point(&b, cos(cub->player.rotation_angle) * MINIPLAYER_RAY_SIZE, \
	sin(cub->player.rotation_angle) * MINIPLAYER_RAY_SIZE);
	if (a.x <= b.x && a.y <= b.y)
		init_point(&pos, a.x, a.y);
	else if (a.x >= b.x && a.y >= b.y)
		init_point(&pos, b.x, b.y);
	else if (a.x <= b.x && a.y >= b.y)
		init_point(&pos, a.x, b.y);
	else if (a.x >= b.x && a.y <= b.y)
		init_point(&pos, b.x, a.y);
	if (draw_line(cub, &direction, pts, MINIPLAYER_RAY_COLOR) < 0)
		return ;
	put_img_to_minimap(cub, &direction, pos.x + center_x, pos.y + center_y);
	mlx_destroy_image(cub->mlx, direction.ptr);
}

static void	player_render(t_cub *cub)
{
	int		x;
	int		y;

	x = ((cub->minimap.width) / 2) - (MINIPLAYER_SIZE);
	y = ((cub->minimap.height) / 2) - (MINIPLAYER_SIZE);
	put_img_to_minimap(cub, &cub->minimap.player, x, y);
	player_direction_render(cub, \
	(cub->minimap.width / 2), (cub->minimap.height / 2));
}

void	minimap_render(t_cub *cub)
{
	int	i;
	int	j;

	background_render(cub);
	rays_render(cub);
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			tile_render(cub, cub->map, i, j);
			j++;
		}
		i++;
	}
	player_render(cub);
	put_img_to_background(cub, &cub->minimap.frame, MINIMAP_X, MINIMAP_Y);
}
