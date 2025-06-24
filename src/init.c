/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/24 10:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	is_line_map(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if ((line[i] == '1' || line[i] == 0) &&
		(line[i + 1] == '1' || line[i + 1] == '0'))
		return (1);
	return (0);
}

static void	get_map_dimensions(t_map *map, int fd)
{
	int	width;
	int	height;
	char	*line;

	height = 0;
	width = 0;
	line = get_next_line(fd);
	while (line && !is_line_map(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && is_line_map(line))
	{
        while (line[width] && line[width] != '\n' && line[width] != '\r')
            width++;
		if (map->width <= width)
			map->width = width;
		free(line);
		line = get_next_line(fd);
		height++;
	}
	free(line);
	map->height = height;
}

static void	init_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = allocate_mem(sizeof(int *), map->height + 1);
	if (!map->grid)
		handle_error(MEMORY_ERROR);
	while (i < map->height)
	{
		map->grid[i] = allocate_mem(sizeof(int), map->width + 1);
		if (!map->grid[i])
			handle_error(MEMORY_ERROR);
		i++;
	}
}

t_game  *init(const char *map_file)
{
    int		fd;
    t_game	*game;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE);
    game = allocate_mem(1, sizeof(t_game));
    game->map = allocate_mem(1, sizeof(t_map));
    game->player = allocate_mem(1, sizeof(t_player));
    game->mlx = allocate_mem(1, sizeof(t_mlx));
    get_map_dimensions(game->map, fd);
	printf("height: %i, width: %i\n", game->map->height, game->map->width);
	init_grid(game->map);
	close(fd);
    return (game);
}