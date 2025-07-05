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
	game->mouse_x = -1;			// BONUS
	game->mouse_pressed = 0;	// BONUS
}

static void	alloc_textures(t_game *game)
{
	int	i;

	game->enemy_tex_path[0] = ft_strdup(TEX_ENEMY0);
	game->enemy_tex_path[1] = ft_strdup(TEX_ENEMY1);
	game->enemy_tex_path[2] = ft_strdup(TEX_ENEMY2);
	game->enemy_tex_path[3] = ft_strdup(TEX_ENEMY3);
	game->goal_tex_path[0] = ft_strdup(TEX_GOAL0);
	game->goal_tex_path[1] = ft_strdup(TEX_GOAL1);
	game->goal_tex_path[2] = ft_strdup(TEX_GOAL2);
	game->goal_tex_path[3] = ft_strdup(TEX_GOAL3);
	i = 0;
	while (i < 4)
	{
		game->texture[i] = allocate_mem(1, sizeof(t_texture));
		game->enemy_texture[i] = allocate_mem(1, sizeof(t_texture));	// BONUS
		game->goal_texture[i] = allocate_mem(1, sizeof(t_texture));		// BONUS
		i++;
	}
	game->texture[i] = allocate_mem(1, sizeof(t_texture));				// BONUS
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
	game->map->door_tex_path = ft_strdup(TEX_DOOR);						// BONUS
	game->player = allocate_mem(1, sizeof(t_player));
	game->player->player_num = 0;
	game->sprites = allocate_mem(game->num_sprites, sizeof(t_sprite));	// BONUS
	game->map->parsed_sprites = 0;										// BONUS
	init_grid(game->map);
	init_buttons(game);
	alloc_textures(game);
	return (game);
}
