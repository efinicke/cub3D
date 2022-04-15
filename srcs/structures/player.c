/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:15:16 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:08:39 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->turn_direction = 0;
	player->walk_direction_h = 0;
	player->walk_direction_v = 0;
	player->walk_speed = PLAYER_WALKSPEED;
	player->turn_speed = PLAYER_TURNSPEED * (PI / 180);
}
