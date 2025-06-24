/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:54 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/18 16:40:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"



int validate_around_space(t_map *map, int y, int x)
{
	if (y == 0 && map->grid[y + 1][x] != ' ' &&  map->grid[y + 1][x] != '1')
		return (0);
	if (y == map->height - 1 && map->grid[y - 1][x] != ' ' &&  map->grid[y - 1][x] != '1')
		return (0);
	if (x > 0 && map->grid[y][x - 1] != ' ' && map->grid[y][x - 1] != '1')
		return (0);
	if (!map->grid[y][x + 1] && map->grid[y][x - 1] != ' ' && map->grid[y][x - 1] != '1')
		return (0);
	return (1);
}

void	validade_first_last_row(t_map *map, int y, int x)
{
	while (x < map->width && map->grid[y][x])
	{
		if (map->grid[y][x] == ' ' && !check_around_space(map, y, x))
			handle_error(INVALID_MAP);
		else if (map->grid[y][x] != '1')
			handle_error(INVALID_MAP);
		x++;
	}
}

void	validate_middle_rows(t_player *player, t_map *map, int y, int x)
{
	while (x < map->width && map->grid[y][x])
	{
		if (map->grid[y][x] == ' ' && !check_around_space(map, y, x))
			handle_error(INVALID_MAP);
		else if (x == 0 || map->grid[x + 1] == NULL || x == map->width - 1)
		{
			if (map->grid[y][x] != '1')
				handle_error(INVALID_MAP);
		}
		else
		{
			if (map->grid[y][x] != '0' || !parse_player(player, map->grid[y][x], x, y))
				handle_error(INVALID_MAP);
		}
		x++;
	}
}

void validate_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		if (y == 0 || y == game->map->height -1)
			validade_first_last_row(game->map, y, x);
		else
			validate_middle_rows(game->player, game->map, y, x);
		y++;
	}
}

void	parse_map(t_game *game, int fd, char *line)
{
	int	width;
	int	height;

	height = 0;
	while (ft_strchr(line, '0') || ft_strchr(line, '1'))
	{
		width = 0;
		while (line[width])
		{
			game->map->grid[height][width] = line[width];
			width++;
		}
		if (game->map->width < width)
			game->map->width = width;
		line = get_next_line(fd);
		height++;
	}
	game->map->height = height;
	while (line)
	{
		if (!empty_line(line))
			handle_error(INVALID_FILE);
		line = get_next_line(fd);
	}
	validate_map(game);
}
