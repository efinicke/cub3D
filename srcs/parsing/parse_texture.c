/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/05 18:17:46 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_texture_path(char **texture, const char *line, \
			unsigned int *i)
{
	unsigned int	path_begin;
	unsigned int	j;

	path_begin = *i;
	while (line[*i] && !(ft_isspace(line[*i])))
		*i += 1;
	if (*i - path_begin == 0)
		return (failure("Missing path after texture declaration"));
	(*texture) = malloc(sizeof(char) * ((*i - path_begin) + 1));
	if (!(*texture))
		return (failure("Malloc failure"));
	j = 0;
	while ((path_begin + j) < *i)
	{
		(*texture)[j] = line[path_begin + j];
		j++;
	}
	(*texture)[j] = '\0';
	return (0);
}

static int	check_texture_path(char **texture)
{
	int	fd;

	fd = open((*texture), O_RDONLY);
	if (fd < 0)
		return (failure("Cannot open the texture file"));
	if (close(fd) < 0)
		return (failure("Cannot close the texture file"));
	return (0);
}

static int	parse_post_texture(const char *line, unsigned int *i)
{
	(void)skip_spaces(line, i);
	if (line[*i] && line[*i] != '\n')
		return (failure("Illegal character found after texture declaration"));
	return (0);
}

int	parse_texture(char **texture, const char *line, unsigned int i)
{
	i += 2;
	if ((*texture))
		return (failure("Texture redefinition"));
	if (skip_spaces(line, &i) == 0)
		return (failure("Missing space after texture declaration"));
	if (parse_texture_path(texture, line, &i) < 0)
		return (-1);
	if (check_texture_path(texture) < 0)
		return (-1);
	if (parse_post_texture(line, &i) < 0)
		return (-1);
	return (0);
}
