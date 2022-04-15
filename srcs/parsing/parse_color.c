/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 12:15:18 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_pre_rgb(const char *line, unsigned int *i, \
			unsigned int color_id, unsigned int *k)
{
	while (line[*i + *k] && ft_isdigit(line[*i + *k]))
		*k += 1;
	if ((color_id != 2 && !(line[*i + *k])) \
	|| (color_id == 2 && !(line[*i + *k]) && *k == 0))
		return (failure("Incomplete color declaration"));
	if (*k == 0)
		return (failure("Illegal character found in color declaration"));
	return (0);
}

static int	parse_rgb(const char *line, unsigned int *i, int *color, \
			unsigned int k)
{
	if (k > 3)
		return (failure("Rgb color operand is too long"));
	if (k == 3 && ft_strncmp(&(line[*i]), "255", 3) > 0)
		return (failure("Rgb color operand value is greater than 255"));
	if (k == 3)
		*color = ((line[*i] - '0') * 100) \
		+ ((line[*i + 1] - '0') * 10) \
		+ (line[*i + 2] - '0');
	if (k == 2)
		*color = ((line[*i] - '0') * 10) \
		+ (line[*i + 1] - '0');
	if (k == 1)
		*color = (line[*i] - '0');
	return (0);
}

static int	parse_post_rgb(const char *line, unsigned int *i, \
			unsigned int color_id)
{
	(void)skip_spaces(line, i);
	if (color_id != 2 && line[*i] && line[*i] != ',')
		return (failure("Missing comma in color declaration"));
	if (color_id != 2 && line[*i] && line[*i] == ',')
		*i += 1;
	if (color_id == 2 && line[*i] && line[*i] != '\n')
		return (failure("Illegal character found after color declaration"));
	(void)skip_spaces(line, i);
	return (0);
}

int	parse_color(int *color, const char *line, unsigned int i)
{
	int				color_rgb[3];
	unsigned int	color_id;
	unsigned int	k;

	i += 1;
	if (*color != -1)
		return (failure("Color redefinition"));
	if (skip_spaces(line, &i) == 0)
		return (failure("Missing space after color declaration"));
	color_id = 0;
	while (color_id < 3)
	{
		k = 0;
		if (parse_pre_rgb(line, &i, color_id, &k) < 0)
			return (-1);
		if (parse_rgb(line, &i, &(color_rgb[color_id]), k) < 0)
			return (-1);
		i += k;
		if (parse_post_rgb(line, &i, color_id) < 0)
			return (-1);
		color_id++;
	}
	*color = (color_rgb[0] << 16) + (color_rgb[1] << 8) + (color_rgb[2]);
	return (0);
}
