/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:57:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:53:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validade_first_last_row(t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->width && map->grid[y][x] != '\0')
	{
		if (map->grid[y][x] == VOID)
		{
			if (!check_around_space(map, y, x))
				handle_error(INVALID_MAP, NULL);
		}
		else if (map->grid[y][x] != WALL)
			handle_error(INVALID_MAP, NULL);
		x++;
	}
}

static void	jump_void(t_map *map, int y, int *x)
{
	while (*x < map->width && map->grid[y][*x] == VOID)
	{
		if (!check_around_space(map, y, *x))
			handle_error(INVALID_MAP, NULL);
		(*x)++;
	}
}

static void	validate_middle_rows(t_map *map, int y)
{
	int	x;

	x = 0;
	jump_void(map, y, &x);
	if (map->grid[y][x] != WALL)
		handle_error(INVALID_MAP, NULL);
	while (x < map->width && map->grid[y][x] == WALL)
		x++;
	if (map->grid[y][x] == EMPTY)
	{
		while (x < map->width && map->grid[y][x] == EMPTY)
			x++;
		if (x < map->width && map->grid[y][x] != WALL)
			handle_error(INVALID_MAP, NULL);
	}
	while (x < map->width && map->grid[y][x])
	{
		if (map->grid[y][x] != WALL && (map->grid[y][x] != VOID))
			handle_error(INVALID_MAP, NULL);
		x++;
	}
}

void	validate_map(t_game *game)
{
	int	y;

	y = 0;
	if (!game->map->width || !game->map->height)
		handle_error(MISSING_MAP, NULL);
	while (y < game->map->height)
	{
		if (y == 0 || y == game->map->height -1)
			validade_first_last_row(game->map, y);
		else
			validate_middle_rows(game->map, y);
		y++;
	}
}
