/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:16:32 by efinicke          #+#    #+#             */
/*   Updated: 2022/04/14 15:54:57 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, 1L << 0, on_keydown, cub);
	mlx_hook(cub->win, ON_KEYUP, 1L << 1, on_keyup, cub);
	mlx_hook(cub->win, ON_DESTROY, 1L << 5, on_destroy, cub);
	mlx_expose_hook(cub->win, render, cub);
	mlx_loop_hook(cub->mlx, render, cub);
	mlx_loop(cub->mlx);
	return (0);
}
