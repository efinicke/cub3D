/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_linux_workaround.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:17:15 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 06:05:58 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Blends the background color with the foreground color to simulate          */
/* transparency.                                                              */
/* alpha is the ratio representing the opacity of the foreground color.       */
/* inv_alpha is the ratio representing the opacity of the background color.   */
/*                                                                            */
/* /!\ The calculation uses the opacity (alpha) of the colors but the first   */
/* value of the colors represents the transparency and not the opacity!       */
/* The colors are represented in ARGB with A being the transparency.          */
/* Thus, 0xff000000 represents a fully transparent color and 0x00000000       */
/* represents a fully opaque color.                                           */
/* /!\ Note that 0xff.0p0f is equivalent to 255.0f                            */

static int	argb_colors_blending(int color_background, int color_foreground)
{
	float	alpha;
	float	inv_alpha;
	int		red;
	int		green;
	int		blue;

	alpha = 1 - ((color_foreground >> 24) & 0xff) / 0xff.0p0f;
	inv_alpha = (1 - alpha);
	red = (int)(((color_background & 0xff0000) >> 16) * inv_alpha \
	+ ((color_foreground & 0xff0000) >> 16) * alpha);
	green = (int)(((color_background & 0x00ff00) >> 8) * inv_alpha \
	+ ((color_foreground & 0x00ff00) >> 8) * alpha);
	blue = (int)((color_background & 0x0000ff) * inv_alpha \
	+ (color_foreground & 0x0000ff) * alpha);
	return (0 << 24 | red << 16 | green << 8 | blue);
}

/* Put each pixel of the image on the background image.                       */
/* If the pixel (color) is completely transparent (0xff...), it is not put.   */
/* If the pixel (color) is completely opaque (0x00...), it is put directly.   */
/* Otherwise it is blended with the background pixel (color).                 */

void	put_img_to_background(t_cub *cub, t_img *img, int x, int y)
{
	int		b_pixel;
	int		f_pixel;
	int		ptr_x;
	int		ptr_y;

	y++;
	ptr_y = fmax(0, -y);
	while (ptr_y < img->height && y + ptr_y <= WINDOW_HEIGHT)
	{
		ptr_x = fmax(0, -x) - 1;
		while (++ptr_x < img->width && x + ptr_x < WINDOW_WIDTH)
		{
			b_pixel = img_get_pixel(&cub->frame, x + ptr_x, y + ptr_y);
			f_pixel = img_get_pixel(img, ptr_x, ptr_y);
			if (((f_pixel >> 24) & 0xff) == 0xff)
				continue ;
			else if (((f_pixel >> 24) & 0xff) == 0x00)
				img_set_pixel(&cub->frame, x + ptr_x, y + ptr_y, \
				f_pixel);
			else
				img_set_pixel(&cub->frame, x + ptr_x, y + ptr_y, \
				argb_colors_blending(b_pixel, f_pixel));
		}
		ptr_y++;
	}
}

/* Put each pixel of the image on the minimap image.                          */
/* If the pixel (color) is completely transparent (0xff...), it is not put.   */
/* If the pixel (color) is completely opaque (0x00...), it is put directly.   */
/* Otherwise it is blended with the background pixel (color).                 */

void	put_img_to_minimap(t_cub *cub, t_img *img, int x, int y)
{
	int		b_pixel;
	int		f_pixel;
	int		ptr_x;
	int		ptr_y;

	y++;
	ptr_y = fmax(0, -y);
	while (ptr_y < img->height && y + ptr_y <= cub->minimap.height)
	{
		ptr_x = fmax(0, -x) - 1;
		while (++ptr_x < img->width && x + ptr_x < cub->minimap.width)
		{
			b_pixel = img_get_pixel(&cub->minimap.frame, x + ptr_x, y + ptr_y);
			f_pixel = img_get_pixel(img, ptr_x, ptr_y);
			if (((f_pixel >> 24) & 0xff) == 0xff)
				continue ;
			else if (((f_pixel >> 24) & 0xff) == 0x00)
				img_set_pixel(&cub->minimap.frame, x + ptr_x, y + ptr_y, \
				f_pixel);
			else
				img_set_pixel(&cub->minimap.frame, x + ptr_x, y + ptr_y, \
				argb_colors_blending(b_pixel, f_pixel));
		}
		ptr_y++;
	}
}
