/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:03:08 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 04:52:02 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_frame(t_cub *cub, t_img *img, int width, int height)
{
	if (init_img(cub, img, width, height) < 0)
		return (-1);
	return (0);
}

int	init_minimap(t_cub *cub)
{
	const int	background_size[2] = {MINIMAP_RATIO_X * MINITILE_SIZE, \
				MINIMAP_RATIO_Y * MINITILE_SIZE};
	const int	tile_size[2] = {MINITILE_SIZE, MINITILE_SIZE};

	cub->minimap.width = MINIMAP_RATIO_X * MINITILE_SIZE;
	cub->minimap.height = MINIMAP_RATIO_Y * MINITILE_SIZE;
	if (init_frame(cub, &cub->minimap.frame, cub->minimap.width, \
		cub->minimap.height) < 0)
		return (failure("Unable to create the minimap frame"));
	if (draw_rect(cub, &cub->minimap.background, background_size, \
		MINIMAP_BACKGROUND_COLOR) < 0)
		return (failure("Unable to create the minimap background shape"));
	if (draw_rect(cub, &cub->minimap.tile_void, tile_size, \
		MINITILE_VOID_COLOR) < 0)
		return (failure("Unable to create the minimap space tile shape"));
	if (draw_rect_unfilled(cub, &cub->minimap.tile_space, tile_size, \
		MINITILE_SPACE_COLOR) < 0)
		return (failure("Unable to create the minimap void tile shape"));
	if (draw_rect(cub, &cub->minimap.tile_wall, tile_size, \
		MINITILE_WALL_COLOR) < 0)
		return (failure("Unable to create the minimap wall tile shape"));
	if (draw_circ(cub, &cub->minimap.player, MINIPLAYER_SIZE, \
		MINIPLAYER_COLOR) < 0)
		return (failure("Unable to create the minimap player shape"));
	return (0);
}

void	destroy_minimap(t_cub *cub)
{
	if (cub->minimap.player.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.player.ptr);
	if (cub->minimap.tile_void.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.tile_void.ptr);
	if (cub->minimap.tile_space.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.tile_space.ptr);
	if (cub->minimap.tile_wall.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.tile_wall.ptr);
	if (cub->minimap.background.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.background.ptr);
	if (cub->minimap.frame.ptr)
		mlx_destroy_image(cub->mlx, cub->minimap.frame.ptr);
}
