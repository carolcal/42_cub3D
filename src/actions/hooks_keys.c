/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:19:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 12:19:20 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward_backward(t_player *p, t_map *map, int key)
{
	double	next[2];

	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (key == W_KEY || key == UP_KEY)
	{
		next[X] += p->dir[X] * (MOVE_SPEED);
		next[Y] += p->dir[Y] * (MOVE_SPEED);
	}
	else if (key == S_KEY || key == DOWN_KEY)
	{
		next[X] -= p->dir[X] * (MOVE_SPEED);
		next[Y] -= p->dir[Y] * (MOVE_SPEED);
	}
	if (map->grid[(int)p->pos[Y]][(int)(next[X])] == 0)
		p->pos[X] = next[X];
	if (map->grid[(int)(next[Y])][(int)p->pos[X]] == 0)
		p->pos[Y] = next[Y];
}

void	move_left_right(t_player *p, t_map *map, int key)
{
	double	next[2];
	double	plane[2];

	if (key == A_KEY)
	{
		plane[X] = p->dir[Y];
		plane[Y] = -p->dir[X];
	}
	else if (key == D_KEY)
	{
		plane[X] = -p->dir[Y];
		plane[Y] = p->dir[X];
	}
	next[X] = p->pos[X] + plane[X] * (MOVE_SPEED);
	next[Y] = p->pos[Y] + plane[Y] * (MOVE_SPEED);
	if (map->grid[(int)p->pos[Y]][(int)(next[X])] == 0)
		p->pos[X] = next[X];
	if (map->grid[(int)(next[Y])][(int)p->pos[X]] == 0)
		p->pos[Y] = next[Y];
}

void	rotate_direction(t_player *p, int key)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == LEFT_KEY)
	{
		old_dir_x = p->dir[X];
		old_plane_x = p->plane[X];
		p->dir[X] = p->dir[X] * cos(-ROT_SPEED) - p->dir[Y] * sin(-ROT_SPEED);
		p->dir[Y] = old_dir_x * sin(-ROT_SPEED) + p->dir[Y] * cos(-ROT_SPEED);
		p->plane[X] = p->plane[X] * cos(-ROT_SPEED)
			- p->plane[Y] * sin(-ROT_SPEED);
		p->plane[Y] = old_plane_x * sin(-ROT_SPEED)
			+ p->plane[Y] * cos(-ROT_SPEED);
	}
	if (key == RIGHT_KEY)
	{
		old_dir_x = p->dir[X];
		old_plane_x = p->plane[X];
		p->dir[X] = p->dir[X] * cos(ROT_SPEED) - p->dir[Y] * sin(ROT_SPEED);
		p->dir[Y] = old_dir_x * sin(ROT_SPEED) + p->dir[Y] * cos(ROT_SPEED);
		p->plane[X] = p->plane[X] * cos(ROT_SPEED)
			- p->plane[Y] * sin(ROT_SPEED);
		p->plane[Y] = old_plane_x * sin(ROT_SPEED)
			+ p->plane[Y] * cos(ROT_SPEED);
	}
}

int	key_press(int key, t_game *game)
{
	if (key == W_KEY || key == UP_KEY)
		game->keys.w = true;
	else if (key == A_KEY)
		game->keys.a = true;
	else if (key == S_KEY || key == DOWN_KEY)
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
	if (key == W_KEY || key == UP_KEY)
		game->keys.w = false;
	else if (key == A_KEY)
		game->keys.a = false;
	else if (key == S_KEY || key == DOWN_KEY)
		game->keys.s = false;
	else if (key == D_KEY)
		game->keys.d = false;
	else if (key == LEFT_KEY)
		game->keys.left = false;
	else if (key == RIGHT_KEY)
		game->keys.right = false;
	return (0);
}
