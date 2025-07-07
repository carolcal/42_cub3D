/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:52:46 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:57:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	is_void_or_wall(int curr)
{
	if (curr == VOID || curr == WALL)
		return (true);
	return (false);
}

bool	is_empty_or_wall(int curr)
{
	if (curr == EMPTY || curr == WALL)
		return (true);
	return (false);
}

static bool	check_above_space(t_map *map, int y, int x)
{
	if (!is_void_or_wall(map->grid[y + 1][x]))
		return (false);
	if (x != map->width - 1)
	{
		if (!is_void_or_wall(map->grid[y][x + 1]))
			return (false);
	}
	if (x != 0)
	{
		if (!is_void_or_wall(map->grid[y][x - 1]))
			return (false);
	}
	return (true);
}

static bool	check_below_space(t_map *map, int y, int x)
{
	if (!is_void_or_wall(map->grid[y - 1][x]))
		return (false);
	if (x != map->width - 1)
	{
		if (!is_void_or_wall(map->grid[y][x + 1]))
			return (false);
	}
	if (x != 0)
	{
		if (!is_void_or_wall(map->grid[y][x - 1]))
			return (false);
	}
	return (true);
}

bool	check_around_space(t_map *map, int y, int x)
{
	if (y != map->height - 1)
		return (check_above_space(map, y, x));
	if (y != 0)
		return (check_below_space(map, y, x));
	return (true);
}
