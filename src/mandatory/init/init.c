/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/03 18:10:05 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_buttons(t_game *game)
{
	game->keys.w = false;
	game->keys.a = false;
	game->keys.s = false;
	game->keys.d = false;
	game->keys.left = false;
	game->keys.right = false;
}

static void	alloc_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i] = allocate_mem(1, sizeof(t_texture));
		i++;
	}
}

t_game	*init(const char *map_file)
{
	t_game	*game;

	game = allocate_mem(1, sizeof(t_game));
	game->mlx = allocate_mem(1, sizeof(t_mlx));
	game->map = allocate_mem(1, sizeof(t_map));
	get_map_dimensions(game, map_file);
	game->map->ceiling = 422;
	game->map->floor = 422;
	game->player = allocate_mem(1, sizeof(t_player));
	game->player->player_num = 0;
	init_grid(game->map);
	init_buttons(game);
	alloc_textures(game);
	return (game);
}
