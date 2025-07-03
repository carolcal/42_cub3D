/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:54 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/03 16:15:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void parse_player_direction(t_player *player)
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

static void    parse_player(t_player *player, char c, int x, int y)
{
	if (player->player_num > 0)
		handle_error(DUPLICATE_PLAYER, NULL);
	player->player_num = 1;
	player->start_dir = c;
	player->pos[X] = x + 0.5;
	player->pos[Y] = y + 0.5;
	player->dir[X] = 0;
	player->dir[y] = 0;
	player->plane[X] = 0;
	player->plane[Y] = 0;
	parse_player_direction(player);
}

static void parse_sprite(t_sprite *sprite, int x, int y)
{
	sprite->pos[X] = x;
	sprite->pos[Y] = y;
	sprite->tex_path[0] = "assets/enemy0.xpm";
	sprite->tex_path[1] = "assets/enemy1.xpm";
	sprite->width = 30;
	sprite->height = 30;
}

static void	parse_map_char(t_game *game, char c, int y, int x)
{
	if (c == '1')
		game->map->grid[y][x] = WALL;
	else if (c == '0')
		game->map->grid[y][x] = EMPTY;
	else if (c == ' ')
		game->map->grid[y][x] = VOID;
	else if (c == 'D')						// BONUS
		game->map->grid[y][x] = DOOR_CLOSE;
	else if (c == 'P')
	{
		game->map->grid[y][x] = EMPTY;
		parse_sprite(game->sprite, x, y);
	}
	else if (ft_strchr("NSEW", c))
	{
		game->map->grid[y][x] = EMPTY;
		parse_player(game->player, c, x, y);
	}
	else
		handle_error("INVALID_MAP", NULL);
}

void	parse_map(t_game *game, int fd, char *line)
{
	int	x;
	int	y;

	y = 0;
	while (line && is_map_line(line))
	{
		x = 0;
		while (line[x] != '\r' && line[x] != '\n' && line[x] != '\0' && x < game->map->width)
		{
			parse_map_char(game, line[x], y, x);
			x++;
		}
		y++;
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!is_empty_line(line))
			handle_error(INVALID_LINE, line);
		line = get_next_line(fd);
	}
}
