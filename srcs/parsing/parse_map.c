/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/05 18:17:46 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	add_line_to_map(char ***map, const char *line, unsigned int index)
{
	unsigned int	j;

	(*map)[index] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!((*map)[index]))
		return (failure("Malloc failure"));
	j = 0;
	while (line[j])
	{
		(*map)[index][j] = line[j];
		j++;
	}
	(*map)[index][j] = '\0';
	(*map)[index + 1] = NULL;
	return (0);
}

int	parse_map(char ***map, const char *line)
{
	char			**ptr;
	unsigned int	i;
	unsigned int	j;

	ptr = (*map);
	i = 0;
	while ((*map) && (*map)[i])
		i++;
	(*map) = malloc(sizeof(char *) * (i + 2));
	if (!((*map)))
	{
		(*map) = ptr;
		return (failure("Malloc failure"));
	}
	j = 0;
	while (ptr && ptr[j])
	{
		(*map)[j] = ptr[j];
		j++;
	}
	if (ptr)
		free(ptr);
	if (add_line_to_map(map, line, i) < 0)
		return (-1);
	return (0);
}
