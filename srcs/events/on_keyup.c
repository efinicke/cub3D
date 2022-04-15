/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_keyup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:33:05 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:08:20 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_keyup(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->player.walk_direction_h = 0;
	else if (keycode == KEY_W)
		cub->player.walk_direction_v = 0;
	else if (keycode == KEY_D)
		cub->player.walk_direction_h = 0;
	else if (keycode == KEY_S)
		cub->player.walk_direction_v = 0;
	else if (keycode == KEY_ARROWLEFT)
		cub->player.turn_direction = 0;
	else if (keycode == KEY_ARROWRIGHT)
		cub->player.turn_direction = 0;
	return (0);
}
