/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:14:09 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 15:16:25 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	handle_keys(t_game *game)
{
	if (game->keys.w)
		move_forward_backward(game->player, game->map, W_KEY);
	if (game->keys.s)
		move_forward_backward(game->player, game->map, S_KEY);
	if (game->keys.a)
		move_left_right(game->player, game->map, A_KEY);
	if (game->keys.d)
		move_left_right(game->player, game->map, D_KEY);
	if (game->keys.left)
		rotate_direction(game->player, LEFT_KEY);
	if (game->keys.right)
		rotate_direction(game->player, RIGHT_KEY);
	return (0);
}

static int	game_loop(t_game *game)
{
	handle_keys(game);
	render_img(game);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx->mlx_ptr, game_loop, game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx->mlx_ptr);
}
