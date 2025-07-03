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

// handle mouse -- BONUS
int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		game->mouse_pressed = 1;
		game->mouse_x = x;
	}
	(void)y;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	if (button == 1)
		game->mouse_pressed = 0;
	(void)x;
	(void)y;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;

	(void)y;
	if (!game->mouse_pressed)
		return (0);
	delta_x = x - game->mouse_x;
	if (delta_x != 0)
		rotate_direction(game->player, delta_x * MOUSE_SENSITIVITY);
	game->mouse_x = x;
	return (0);
}

// handle keys
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

static int	handle_keys(t_game *game)
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

static int	game_loop(t_game *game)
{
	handle_keys(game);
	update_sprites(game); //BONUS
	render_img(game);
	if (player_touch_sprite(game)) //BOUS
	{
		printf("Xiii, ele te pegou no flagra!\n"); //trocar para ingles na aval
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
