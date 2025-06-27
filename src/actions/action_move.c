/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:35:17 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 18:35:17 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_player *p, t_map *map)
{
	double	dir[2];
	double	next[2];

	dir[X] = p->dir[X] * MOVE_SPEED;
	dir[Y] = p->dir[Y] * MOVE_SPEED;
	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (dir[X] > 0)
		if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + dir[X] + COLLISION_OFFSET)] == 0)
			next[X] += dir[X];
	if (dir[X] <= 0)
		if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + dir[X] - COLLISION_OFFSET)] == 0)
			next[X] += dir[X];
	if (dir[Y] > 0)
		if (map->grid[(int)(p->pos[Y] + dir[Y] + COLLISION_OFFSET)][(int)p->pos[X]] == 0)
			next[Y] += dir[Y];
	if (dir[Y] <= 0)
		if (map->grid[(int)(p->pos[Y] + dir[Y] - COLLISION_OFFSET)][(int)p->pos[X]] == 0)
			next[Y] += dir[Y];
	p->pos[X] = next[X];
	p->pos[Y] = next[Y];
}

void	move_backward(t_player *p, t_map *map)
{
	double	dir[2];
	double	next[2];

	dir[X] = p->dir[X] * MOVE_SPEED;
	dir[Y] = p->dir[Y] * MOVE_SPEED;
	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (dir[X] > 0)
		if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] - dir[X] - COLLISION_OFFSET)] == 0)
			next[X] -= dir[X];
	if (dir[X] <= 0)
		if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] - dir[X] + COLLISION_OFFSET)] == 0)
			next[X] -= dir[X];
	if (dir[Y] > 0)
		if (map->grid[(int)(p->pos[Y] - dir[Y] - COLLISION_OFFSET)][(int)p->pos[X]] == 0)
			next[Y] -= dir[Y];
	if (dir[Y] <= 0)
		if (map->grid[(int)(p->pos[Y] - dir[Y] + COLLISION_OFFSET)][(int)p->pos[X]] == 0)
			next[Y] -= dir[Y];
	p->pos[X] = next[X];
	p->pos[Y] = next[Y];
}

void	strafe_left(t_player *p, t_map *map)
{
	double	plane[2];
	double	offset[2];

	plane[X] = p->dir[Y] * MOVE_SPEED;
	plane[Y] = -p->dir[X] * MOVE_SPEED;

	if (plane[X] > 0)
		offset[X] = COLLISION_OFFSET;
	else
		offset[X] = -COLLISION_OFFSET;
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + plane[X] + offset[X])] == 0)
		p->pos[X] += plane[X];

	if (plane[Y] > 0)
		offset[Y] = COLLISION_OFFSET;
	else
		offset[Y] = -COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] + plane[Y] + offset[Y])][(int)p->pos[X]] == 0)
		p->pos[Y] += plane[Y];
}

void	strafe_right(t_player *p, t_map *map)
{
	double	plane[2];
	double	offset[2];

	plane[X] = -p->dir[Y] * MOVE_SPEED;
	plane[Y] = p->dir[X] * MOVE_SPEED;

	if (plane[X] > 0)
		offset[X] = COLLISION_OFFSET;
	else
		offset[X] = -COLLISION_OFFSET;
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + plane[X] + offset[X])] == 0)
		p->pos[X] += plane[X];

	if (plane[Y] > 0)
		offset[Y] = COLLISION_OFFSET;
	else
		offset[Y] = -COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] + plane[Y] + offset[Y])][(int)p->pos[X]] == 0)
		p->pos[Y] += plane[Y];
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
