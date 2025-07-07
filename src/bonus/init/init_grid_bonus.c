/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:33:44 by marvin            #+#    #+#             */
/*   Updated: 2025/07/04 21:33:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	count_sprites(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (line[i] == 'P' || line[i] == 'G')
			count++;
		i++;
	}
	return (count);
}

static int	get_line_width(const char *line)
{
	int	width;

	width = 0;
	while (line[width] && line[width] != '\n' && line[width] != '\r')
		width++;
	return (width);
}

void	get_map_dimensions(t_game *game, const char *map_file)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	game->num_sprites = 0;
	game->map->width = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE, (char *)map_file);
	line = get_next_line(fd);
	while (line && !is_map_line(line))
		line = get_next_line(fd);
	while (line && is_map_line(line))
	{
		game->num_sprites += count_sprites(line);
		game->map->width = fmax(game->map->width, get_line_width(line));
		line = get_next_line(fd);
		height++;
	}
	game->map->height = height;
	get_next_line(-42);
	close(fd);
}

static void	fill_grid(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->grid[y][x] = VOID;
			x++;
		}
		y++;
	}
}

void	init_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = allocate_mem(sizeof(int *), map->height + 1);
	if (!map->grid)
		handle_error(MEMORY_ERROR, NULL);
	while (i < map->height)
	{
		map->grid[i] = allocate_mem(sizeof(int), map->width + 1);
		if (!map->grid[i])
			handle_error(MEMORY_ERROR, NULL);
		i++;
	}
	fill_grid(map);
}
