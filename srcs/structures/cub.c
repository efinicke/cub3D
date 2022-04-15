/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:13:12 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 17:04:52 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_cub_graphics(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!(cub->mlx))
		return (failure("Unable to set up the connection to the X server"));
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!(cub->mlx))
		return (failure("Unable to create a new window"));
	if (init_img(cub, &cub->frame, WINDOW_WIDTH, WINDOW_HEIGHT) < 0)
		return (failure("Unable to create the main frame"));
	if (init_minimap(cub) < 0)
		return (-1);
	if (init_textures(cub) < 0)
		return (-1);
	init_player(&cub->player);
	return (1);
}

int	init_cub(t_cub *cub, const char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (failure("Cannot open the scene description file"));
	if (parse_cub_file(cub, fd) < 0)
	{
		if (close(fd) < 0)
			return (failure("Cannot close the scene description file"));
		return (-1);
	}
	if (close(fd) < 0)
		return (failure("Cannot close the scene description file"));
	return (0);
}

static void	destroy_cub_elements(t_cub *cub)
{
	unsigned int	i;

	if (cub->frame.ptr)
		mlx_destroy_image(cub->mlx, cub->frame.ptr);
	if (cub->mlx && cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
	if (cub->mlx)
		free(cub->mlx);
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	i = 0;
	while (cub->map && cub->map[i])
		free(cub->map[i++]);
	if (cub->map)
		free(cub->map);
}

void	delete_cub(t_cub *cub)
{
	if (!(cub))
		return ;
	destroy_textures(cub);
	destroy_minimap(cub);
	destroy_cub_elements(cub);
}
