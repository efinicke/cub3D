/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/12 03:16:37 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_character(char *c)
{
	if (ft_isspace(*c))
		*c = ' ';
	if (*c != ' ' \
	&& *c != '0' && *c != '1' \
	&& *c != 'N' && *c != 'S' \
	&& *c != 'E' && *c != 'W')
		return (failure("Illegal character found in the map content"));
	return (0);
}

static int	check_player_position(char c, unsigned int *player, int last_line)
{
	if (c == 'N' || c == 'S' \
	|| c == 'E' || c == 'W')
		*player += 1;
	if (*player > 1)
		return (failure("Too many player's starting position"));
	if (last_line && *player < 1)
		return (failure("Missing player's starting position"));
	else
		return (0);
}

static int	check_closure(char **map, unsigned int i, unsigned int j, \
			const unsigned int size)
{
	if (map[i][j] == '0' \
	|| map[i][j] == 'N' || map[i][j] == 'S' \
	|| map[i][j] == 'E' || map[i][j] == 'W')
	{
		if (i == 0 || i == size || j == 0 || ft_strlen(map[i]) == j + 1)
			return (failure("The map is not closed"));
		if (ft_strlen(map[i - 1]) < (j + 2) || map[i - 1][j - 1] == ' ' \
		|| map[i - 1][j] == ' ' || map[i - 1][j + 1] == ' ' \
		|| ft_strlen(map[i]) < (j + 2) || map[i][j - 1] == ' ' \
		|| map[i][j + 1] == ' ' \
		|| ft_strlen(map[i + 1]) < (j + 2) || map[i + 1][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
			return (failure("The map is not closed"));
	}
	return (0);
}

static unsigned int	get_size(char **map)
{
	unsigned int	i;

	if (!(map) || !(map[0]))
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i - 1);
}

int	check_map(char **map)
{
	const unsigned int	size = get_size(map);
	unsigned int		player;
	unsigned int		i;
	unsigned int		j;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_character(&map[i][j]) < 0)
				return (-1);
			if (check_player_position(map[i][j], &player, i == size) < 0)
				return (-1);
			if (check_closure(map, i, j, size) < 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
