/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:54 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/03 15:26:49 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	parse_player_direction(t_player *player)
{
	if (player->start_dir == 'W')
	{
		player->dir[X] = -1;
		player->plane[Y] = -tan((FOV * M_PI / 180.0) / 2.0);
	}
	else if (player->start_dir == 'E')
	{
		player->dir[X] = 1;
		player->plane[Y] = tan((FOV * M_PI / 180.0) / 2.0);
	}
	else if (player->start_dir == 'S')
	{
		player->dir[Y] = 1;
		player->plane[X] = -tan((FOV * M_PI / 180.0) / 2.0);
	}
	else if (player->start_dir == 'N')
	{
		player->dir[Y] = -1;
		player->plane[X] = tan((FOV * M_PI / 180.0) / 2.0);
	}
	else
		handle_error(INVALID_PLAYER, NULL);
}

static void	parse_player(t_player *player, char c, int x, int y)
{
	if (player->player_num > 0)
		handle_error(DUPLICATE_PLAYER, NULL);
	player->player_num = 1;
	player->start_dir = c;
	player->pos[X] = x + 0.5;
	player->pos[Y] = y + 0.5;
	player->dir[X] = 0;
	player->dir[Y] = 0;
	player->plane[X] = 0;
	player->plane[Y] = 0;
	parse_player_direction(player);
}

static void	parse_sprite(t_game *game, char c, int x, int y)
{
	t_sprite	*sprite;
	int			**grid;

	sprite = &game->sprites[game->map->sprite_n];
	grid = game->map->grid;
	sprite->pos[X] = x + 0.5;
	sprite->pos[Y] = y + 0.5;
	if (grid[y + 1][x] == '1')
		sprite->dir[Y] = -1.0;
	else
		sprite->dir[Y] = 1.0;
	if (grid[y][x + 1] == '1')
		sprite->dir[X] = -1.0;
	else
		sprite->dir[X] = 1.0;
	sprite->radius = 0.5;
	if (c == 'P')
		sprite->enemy = true;
	else
		sprite->enemy = false;
	game->map->sprite_n++;
}

static void	parse_map_char(t_game *game, char c, int y, int x)
{
	if (c == '1')
		game->map->grid[y][x] = WALL;
	else if (c == '0')
		game->map->grid[y][x] = EMPTY;
	else if (c == ' ')
		game->map->grid[y][x] = VOID;
	else if (c == 'D')
		game->map->grid[y][x] = DOOR_CLOSE;
	else if (ft_strchr("PG", c))
	{
		game->map->grid[y][x] = EMPTY;
		parse_sprite(game, c, x, y);
	}
	else if (ft_strchr("NSEW", c))
	{
		game->map->grid[y][x] = EMPTY;
		parse_player(game->player, c, x, y);
	}
	else
		handle_error(INVALID_MAP, "Undetected char.");
}

void	parse_map(t_game *game, int fd, char *line)
{
	int	x;
	int	y;

	y = 0;
	while (line && is_map_line(line))
	{
		x = 0;
		while (line[x] != '\r' && line[x] != '\n' && line[x] != '\0'
			&& x < game->map->width)
		{
			parse_map_char(game, line[x], y, x);
			x++;
		}
		y++;
		line = get_next_line(fd);
	}
	while (line)
	{
		printf("line:%s", line);
		if (!is_empty_line(line))
			handle_error(INVALID_LINE, line);
		line = get_next_line(fd);
	}
}
