/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:17:15 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/25 17:17:15 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

voidmove_forward_backward(t_player *p, t_map *map, int key)
{
	double	next[2];

	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (key == W_KEY)
	{
		next[X] += p->dir[X] * (MOVE_SPEED + COLLISION_OFFSET);
		next[Y] += p->dir[Y] * (MOVE_SPEED + COLLISION_OFFSET);
	}
	else if (key == S_KEY)
	{
		next[X] -= p->dir[X] * (MOVE_SPEED + COLLISION_OFFSET);
		next[Y] -= p->dir[Y] * (MOVE_SPEED + COLLISION_OFFSET);
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
	next[X] = p->pos[X] + plane[X] * (MOVE_SPEED + COLLISION_OFFSET);
	next[Y] = p->pos[Y] + plane[Y] * (MOVE_SPEED + COLLISION_OFFSET);
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
		p->plane[X] = p->plane[X] * cos(-ROT_SPEED) - p->plane[Y] * sin(-ROT_SPEED);
		p->plane[Y] = old_plane_x * sin(-ROT_SPEED) + p->plane[Y] * cos(-ROT_SPEED);
	}
	if (key == RIGHT_KEY)
	{
		old_dir_x = p->dir[X];
		old_plane_x = p->plane[X];
		p->dir[X] = p->dir[X] * cos(ROT_SPEED) - p->dir[Y] * sin(ROT_SPEED);
		p->dir[Y] = old_dir_x * sin(ROT_SPEED) + p->dir[Y] * cos(ROT_SPEED);
		p->plane[X] = p->plane[X] * cos(ROT_SPEED) - p->plane[Y] * sin(ROT_SPEED);
		p->plane[Y] = old_plane_x * sin(ROT_SPEED) + p->plane[Y] * cos(ROT_SPEED);
	}
}

int	handle_keys(int key, t_game *game)
{
	if (key == ESC_KEY)
		close_window(game);
	else if (key == W_KEY || key == S_KEY)
		move_forward_backward(game->player, game->map, key);
	else if (key == A_KEY || key == D_KEY)
		move_left_right(game->player, game->map, key);
	else if (key == LEFT_KEY || key == RIGHT_KEY)
		rotate_direction(game->player, key);
	return (0);
}
