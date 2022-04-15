/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 12:00:13 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_empty(const char *s)
{
	unsigned int	i;

	if (!(s))
		return (1);
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i])
		return (0);
	else
		return (1);
}

static int	parse_textures_and_colors(t_cub *cub, const char *line)
{
	unsigned int	i;

	i = 0;
	(void)skip_spaces(line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_texture(&cub->no, line, i));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_texture(&cub->so, line, i));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_texture(&cub->we, line, i));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_texture(&cub->ea, line, i));
	else if (line[i] == 'F')
		return (parse_color(&cub->f, line, i));
	else if (line[i] == 'C')
		return (parse_color(&cub->c, line, i));
	else if (line[i] == '1')
		return (failure("The map content is not the last element \
of the scene description file"));
	else
		return (failure("Illegal character found"));
}

static int	check_map_split(const char *line)
{
	static unsigned int	end_flag = 0;
	unsigned int		i;

	if (!(line) || is_empty(line))
		end_flag = 1;
	else
	{
		if (end_flag == 1)
		{
			i = 0;
			while (line[i])
			{
				if (!(ft_isspace(line[i])) \
				&& line[i] != '0' && line[i] != '1' && line[i] != 'N' \
				&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
					return (failure("Illegal character found"));
				i++;
			}
			return (failure("The map is split"));
		}
	}
	return (0);
}

static int	parse_map_and_player(t_cub *cub, const char *line)
{
	unsigned int		i;

	i = 0;
	if (check_map_split(line) < 0)
		return (-1);
	if (!(line) || is_empty(line))
		return (0);
	if (ft_isspace(line[i]) \
	|| line[i] == '0' || line[i] == '1' || line[i] == 'N' \
	|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
	{
		if (parse_map(&cub->map, line) < 0)
			return (-1);
		if (parse_player(cub, cub->map, line) < 0)
			return (-1);
		return (0);
	}
	else
		return (failure("Illegal character found"));
}

int	parse_line(t_cub *cub, const char *line)
{
	if (!(line) || (is_empty(line) && !(cub->map)))
		return (0);
	if (!(cub->no) || !(cub->so) || !(cub->we) || !(cub->ea) \
	|| cub->f == -1 || cub->c == -1)
	{
		return (parse_textures_and_colors(cub, line));
	}
	else
	{
		return (parse_map_and_player(cub, line));
	}
}
