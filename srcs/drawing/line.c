/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:16:57 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:07:58 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_inferior(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

static int	l_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

/* Bresenham's line algorithm                                                 */

static void	draw(t_img *img, t_ipoint *pts[3], int color)
{
	const int	dx = l_abs(pts[1]->x - pts[0]->x);
	const int	sx = is_inferior(pts[0]->x, pts[1]->x);
	const int	dy = -l_abs(pts[1]->y - pts[0]->y);
	const int	sy = is_inferior(pts[0]->y, pts[1]->y);
	int			error;

	error = dx + dy;
	while (pts[0]->x != pts[1]->x || pts[0]->y != pts[1]->y)
	{
		img_set_pixel(img, pts[0]->x - pts[2]->x, pts[0]->y - pts[2]->y, color);
		if ((2 * error) >= dy)
		{
			if (pts[0]->x == pts[1]->x)
				break ;
			error = error + dy;
			pts[0]->x = pts[0]->x + sx;
		}
		if ((2 * error) <= dx)
		{
			if (pts[0]->y == pts[1]->y)
				break ;
			error = error + dx;
			pts[0]->y = pts[0]->y + sy;
		}
	}
}

/* Create and image containing a line.                                        */
/* There are 4 possible image position. The right one for a correct display   */
/* must be determined outside this function.                                  */

int	draw_line(t_cub *cub, t_img *img, t_ipoint *pts[3], int color)
{
	const int	wh[2] = {l_abs(pts[0]->x - pts[1]->x) + 1, \
						l_abs(pts[0]->y - pts[1]->y) + 1};

	if (pts[0]->x == pts[1]->x && pts[0]->y == pts[1]->y)
		return (-1);
	if (init_img(cub, img, wh[0], wh[1]) < 0)
		return (-1);
	img_fill(img, 0xff000000);
	draw(img, pts, color);
	return (0);
}
