/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:54 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/24 10:11:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int check_around_space(t_map *map, int y, int x)
{
	if (map->grid[y][x])
	{
		if (!is_space_or_one(map->grid[y][x + 1]))
			return (0);
	}
	if (y != map->height - 1)
	{
		if (!is_space_or_one(map->grid[y + 1][x - 1]) ||
			!is_space_or_one(map->grid[y + 1][x + 1]) ||
			!is_space_or_one(map->grid[y + 1][x]))
		return (0);
	}
	if (y != 0)
	{
		if (!is_space_or_one(map->grid[y - 1][x - 1]) ||
			!is_space_or_one(map->grid[y - 1][x + 1]) ||
			!is_space_or_one(map->grid[y - 1][x]))
		return (0);
	}
	return (1);
}

void	validade_first_last_row(t_map *map, int y)
{
	int	x;
	printf("y=%i\n", y);
	x = 0;
	while (x < map->width && map->grid[y][x] != '\0')
	{
		printf("%c\n", map->grid[y][x]);
		if (map->grid[y][x] == ' ' && !check_around_space(map, y, x))
			handle_error("INVALID_MAP1\n");
		else if (map->grid[y][x] != '1')
			handle_error("INVALID_MAP2\n");
		x++;
	}
}

void	validate_middle_rows(t_player *player, t_map *map, int y)
{
	int	x;

	x = 0;
	printf("middle y=%i", y);
	while (x < map->width && map->grid[y][x])
	{
		if (map->grid[y][x] == ' ' && !check_around_space(map, y, x))
			handle_error("INVALID_MAP3");
		else if (x == 0 || map->grid[x + 1] == NULL || x == map->width - 1)
		{
			if (map->grid[y][x] != '1')
				handle_error("INVALID_MAP4");
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
	int y;

	y = 0;
	while (y < game->map->height)
	{
		if (y == 0 || y == game->map->height -1)
			validade_first_last_row(game->map, y);
		else
			validate_middle_rows(game->player, game->map, y);
		y++;
	}
}

void	parse_map(t_game *game, int fd, char *line)
{
	int	x;
	int	y;
	printf("parse map\n");
	y = 0;
	while (line && (ft_strchr(line, '0') || ft_strchr(line, '1')))
	{
		x = 0;
		while(line[x] != '\n' && line[x] !='\0')
		{
			game->map->grid[y][x] = line[x];
			x++;
		}
		y++;
		line = get_next_line(fd);
	}
	printf("parsed!\n");
	while (line)
	{
		if (!empty_line(line))
			handle_error(INVALID_FILE);
		line = get_next_line(fd);
	}
	validate_map(game);
}
