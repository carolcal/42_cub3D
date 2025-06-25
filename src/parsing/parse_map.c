/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:54 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/25 17:23:45 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	parse_player(t_player *player, char c, int x, int y)
{
	if (player->player_num > 0)
		handle_error(DUPLICATE_PLAYER, NULL);
	player->player_num = 1;
	player->pos[X] = x;
	player->pos[Y] = y;
	if (c == 'N' || c == 'S')
	{
		player->dir[0] = NORTH_SOUTH;
		if (c == 'N')
			player->dir[1] = LEFT;
		else
			player->dir[1] = RIGHT;
	}
	else
	{
		player->dir[0] = WEST_EAST;
		if (c == 'W')
			player->dir[1] = LEFT;
		else
			player->dir[1] = RIGHT;
	}
}

void	parse_map_char(t_game *game, char c, int y, int x)
{
	if (c == '1')
		game->map->grid[y][x] = WALL;
	else if (c == '0')
		game->map->grid[y][x] = EMPTY;
	else if (c == ' ')
		game->map->grid[y][x] = VOID;
	else if (ft_strchr("NSEW", c))
	{
		game->map->grid[y][x] = EMPTY;
		parse_player(game->player, c, x, y);
	}
	else
		handle_error(INVALID_MAP, NULL);
}

void	parse_map(t_game *game, int fd, char *line)
{
	int	x;
	int	y;

	y = 0;
	while (line && is_map_line(line))
	{
		x = 0;
		while(line[x] != '\n' && line[x] !='\0' && x < game->map->width)
		{
			parse_map_char(game, line[x], y, x);
			x++;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!is_empty_line(line))
			handle_error(INVALID_LINE, line);
		free(line);
		line = get_next_line(fd);
	}
}
