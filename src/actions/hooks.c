/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:14:09 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 18:54:37 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	try_toggle_door(t_game *game)	// BONUS
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player->pos[X] + game->player->dir[X]
			* (1 + COLLISION_OFFSET));
	map_y = (int)(game->player->pos[Y] + game->player->dir[Y]
			* (1 + COLLISION_OFFSET));
	if (map_x < 0 || map_x >= game->map->width
		|| map_y < 0 || map_y >= game->map->height)
		return ;
	if (game->map->grid[map_y][map_x] == DOOR_CLOSE)
		game->map->grid[map_y][map_x] = DOOR_OPEN;
	else if (game->map->grid[map_y][map_x] == DOOR_OPEN)
		game->map->grid[map_y][map_x] = DOOR_CLOSE;
}

static int	game_loop(t_game *game)
{
	int	touch_sprite;

	handle_keys(game);
	update_sprites(game); //BONUS
	render_img(game);
	touch_sprite = player_touch_sprite(game);
	if (touch_sprite) //BONUS
	{
		if (touch_sprite == 1)
			printf("You LOST!\n");
		else
			printf("You WIN!\n");
		close_window(game);
	}
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx->mlx_ptr, game_loop, game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win_ptr, 4, 1L << 2, mouse_press, game);	// bonus
	mlx_hook(game->mlx->win_ptr, 5, 1L << 3, mouse_release, game);	// bonus
	mlx_hook(game->mlx->win_ptr, 6, 1L << 6, mouse_move, game);		// bonus
	mlx_hook(game->mlx->win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx->mlx_ptr);
}
