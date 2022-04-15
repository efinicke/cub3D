/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_keydown.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:33:05 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/14 16:21:17 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keydown(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->player.walk_direction_h = -1;
	else if (keycode == KEY_W)
		cub->player.walk_direction_v = +1;
	else if (keycode == KEY_D)
		cub->player.walk_direction_h = +1;
	else if (keycode == KEY_S)
		cub->player.walk_direction_v = -1;
	else if (keycode == KEY_ARROWLEFT)
		cub->player.turn_direction = -1;
	else if (keycode == KEY_ARROWRIGHT)
		cub->player.turn_direction = +1;
	else if (keycode == KEY_ESC)
		mlx_loop_end(cub->mlx);
	return (0);
}
