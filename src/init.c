/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/27 15:25:11 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_map_dimensions(t_map *map, const char *map_file)
{
	int		width;
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE, (char *)map_file);
	line = get_next_line(fd);
	while (line && !is_map_line(line))
		line = get_next_line(fd);
	while (line && is_map_line(line))
	{
		width = 0;
		while (line[width] && line[width] != '\n' && !ft_isspace(line[width]))
			width++;
		if (map->width <= width)
			map->width = width;
		line = get_next_line(fd);
		height++;
	}
	map->height = height;
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

static void	init_grid(t_map *map)
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

t_game	*init(const char *map_file)
{
	int		i;
	t_game	*game;

	i = 0;
	game = allocate_mem(1, sizeof(t_game));
	game->map = allocate_mem(1, sizeof(t_map));
	get_map_dimensions(game->map, map_file);
	game->map->ceiling = 422;
	game->map->floor = 422;
	game->player = allocate_mem(1, sizeof(t_player));
	game->player->player_num = 0;
	game->mlx = allocate_mem(1, sizeof(t_mlx));
	while (i < 4)
	{
		game->texture[i] = allocate_mem(1, sizeof(t_texture));
		i++;
	}
	game->keys.w = false;
	game->keys.a = false;
	game->keys.s = false;
	game->keys.d = false;
	game->keys.left = false;
	game->keys.right = false;
	init_grid(game->map);
	return (game);
}
