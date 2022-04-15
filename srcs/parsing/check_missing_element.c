/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_missing_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 03:22:41 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/13 11:50:14 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_missing_element(const t_cub *cub)
{
	if (!(cub->no))
		return (failure("Missing north texture"));
	if (!(cub->so))
		return (failure("Missing south texture"));
	if (!(cub->ea))
		return (failure("Missing east texture"));
	if (!(cub->we))
		return (failure("Missing west texture"));
	if (cub->f == -1)
		return (failure("Missing floor color"));
	if (cub->c == -1)
		return (failure("Missing ceiling color"));
}
