/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 04:34:18 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_puterror_msg(int code)
{
	ft_putstr_fd("Error\n", STDERR);
	if (code == 1)
		ft_putstr_fd("Usage : ./cub3d [map_path]\n", STDERR);
	else if (code == 2)
		ft_putstr_fd("The file passed in argument must be a .cub file.\n", \
		STDERR);
	return (1);
}

static int	is_cub_file(char *filename)
{
	const size_t	len = ft_strlen(filename);

	return (filename[len - 4] == '.' \
	&& filename[len - 3] == 'c' \
	&& filename[len - 2] == 'u' \
	&& filename[len - 1] == 'b' );
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_puterror_msg(1));
	if (!(is_cub_file(argv[1])))
		return (ft_puterror_msg(2));
	if (init_cub(&cub, argv[1]) < 0)
		return (1);
	if (init_cub_graphics(&cub) < 0)
	{
		delete_cub(&cub);
		return (1);
	}
	game_loop(&cub);
	delete_cub(&cub);
	return (0);
}
