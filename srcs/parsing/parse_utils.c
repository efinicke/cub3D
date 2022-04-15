/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:02:26 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 12:29:14 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	skip_spaces(const char *s, unsigned int *i)
{
	unsigned int	j;

	if (!(s))
		return (0);
	j = 0;
	while (s[*i + j] && ft_isspace(s[*i + j]))
		j++;
	*i += j;
	return (j);
}
