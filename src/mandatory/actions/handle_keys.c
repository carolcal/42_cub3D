/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:19:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 12:19:20 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key, t_game *game)
{
	if (key == W_KEY)
		game->keys.w = true;
	else if (key == A_KEY)
		game->keys.a = true;
	else if (key == S_KEY)
		game->keys.s = true;
	else if (key == D_KEY)
		game->keys.d = true;
	else if (key == LEFT_KEY)
		game->keys.left = true;
	else if (key == RIGHT_KEY)
		game->keys.right = true;
	else if (key == ESC_KEY)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W_KEY)
		game->keys.w = false;
	else if (key == A_KEY)
		game->keys.a = false;
	else if (key == S_KEY)
		game->keys.s = false;
	else if (key == D_KEY)
		game->keys.d = false;
	else if (key == LEFT_KEY)
		game->keys.left = false;
	else if (key == RIGHT_KEY)
		game->keys.right = false;
	return (0);
}

int	handle_keys(t_game *game)
{
	if (game->keys.w)
		move_forward(game->player, game->map);
	if (game->keys.s)
		move_backward(game->player, game->map);
	if (game->keys.a)
		strafe_left(game->player, game->map);
	if (game->keys.d)
		strafe_right(game->player, game->map);
	if (game->keys.left)
		rotate_direction(game->player, -ROT_SPEED);
	if (game->keys.right)
		rotate_direction(game->player, ROT_SPEED);
	return (0);
}
