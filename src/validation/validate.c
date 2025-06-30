/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:53:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:54:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate(t_game *game)
{
	validate_textures(game->map->tex_path);
	validate_colors(game->map);
	validate_map(game);
	validate_player(game);
}

void	validate_textures(char *texture[4])
{
	int	i;
	int	fd;
	int	len;

	i = 0;
	while (i < 4)
	{
		if (!texture[i])
			handle_error(MISSING_TEXTURE, NULL);
		len = ft_strlen(texture[i]);
		if (len < 5)
			handle_error(INVALID_TEXTURE, texture[i]);
		if (ft_strncmp(texture[i] + len - 4, ".xpm", 4) != 0)
			handle_error(INVALID_TEXTURE, texture[i]);
		fd = open(texture[i], O_RDONLY);
		if (fd < 0)
			handle_error(INVALID_TEXTURE, texture[i]);
		close(fd);
		i++;
	}
}

void	validate_colors(t_map *map)
{
	if (map->ceiling == 422)
		handle_error(MISSING_COLOR, "ceiling");
	if (map->floor == 422)
		handle_error(MISSING_COLOR, "floor");
}

void	validate_player(t_game *game)
{
	int	x;
	int	y;

	x = game->player->pos[X];
	y = game->player->pos[Y];
	if (game->player->player_num == 0)
		handle_error(MISSING_PLAYER, NULL);
	if (!is_empty_or_wall(game->map->grid[y - 1][x - 1]) ||
		!is_empty_or_wall(game->map->grid[y - 1][x]) ||
		!is_empty_or_wall(game->map->grid[y - 1][x + 1]) ||
		!is_empty_or_wall(game->map->grid[y][x - 1]) ||
		!is_empty_or_wall(game->map->grid[y - 1][x + 1]) ||
		!is_empty_or_wall(game->map->grid[y + 1][x - 1]) ||
		!is_empty_or_wall(game->map->grid[y + 1][x]) ||
		!is_empty_or_wall(game->map->grid[y + 1][x + 1]))
		handle_error(INVALID_PLAYER, NULL);
}
