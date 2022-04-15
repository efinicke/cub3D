/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 04:59:55 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/14 15:57:14 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	move_player(t_cub *cub, t_player *player, char **map)
{
	float	new_player_x;
	float	new_player_y;
	float	move_step_v;
	float	move_step_h;

	move_step_v = player->walk_direction_v * player->walk_speed;
	move_step_h = player->walk_direction_h * player->walk_speed;
	player->rotation_angle += player->turn_direction * player->turn_speed;
	new_player_x = player->x;
	new_player_y = player->y;
	new_player_x += cos(player->rotation_angle) * move_step_v;
	new_player_y += sin(player->rotation_angle) * move_step_v;
	new_player_x += cos(player->rotation_angle + HALF_PI) * move_step_h;
	new_player_y += sin(player->rotation_angle + HALF_PI) * move_step_h;
	if (!(map_has_wall_at(cub, map, new_player_x, new_player_y)))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}

int	render(t_cub *cub)
{
	move_player(cub, &cub->player, cub->map);
	cast_all_rays(cub);
	generate_3d_projection(cub, &cub->frame, &cub->minimap.tile_wall);
	minimap_render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.ptr, 0, 0);
	return (0);
}
