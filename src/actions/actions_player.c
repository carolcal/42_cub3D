/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
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
	double	offset;

	dir[X] = p->dir[X] * MOVE_SPEED;
	dir[Y] = p->dir[Y] * MOVE_SPEED;
	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (dir[X] > 0)
		offset = COLLISION_OFFSET;
	else
		offset = -COLLISION_OFFSET;
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + dir[X] + offset)] <= 0)		// <= 0 para o bonus - repete nos outros
		next[X] += dir[X];
	if (dir[Y] > 0)
		offset = COLLISION_OFFSET;
	else
		offset = -COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] + dir[Y] + offset)][(int)p->pos[X]] <= 0)
		next[Y] += dir[Y];
	p->pos[X] = next[X];
	p->pos[Y] = next[Y];
}

void	move_backward(t_player *p, t_map *map)
{
	double	dir[2];
	double	next[2];
	double	offset;

	dir[X] = p->dir[X] * MOVE_SPEED;
	dir[Y] = p->dir[Y] * MOVE_SPEED;
	next[X] = p->pos[X];
	next[Y] = p->pos[Y];
	if (dir[X] > 0)
		offset = -COLLISION_OFFSET;
	else
		offset = COLLISION_OFFSET;
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] - dir[X] + offset)] <= 0)
		next[X] -= dir[X];
	if (dir[Y] > 0)
		offset = -COLLISION_OFFSET;
	else
		offset = COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] - dir[Y] + offset)][(int)p->pos[X]] <= 0)
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
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + plane[X] + offset[X])] <= 0)
		p->pos[X] += plane[X];
	if (plane[Y] > 0)
		offset[Y] = COLLISION_OFFSET;
	else
		offset[Y] = -COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] + plane[Y] + offset[Y])][(int)p->pos[X]] <= 0)
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
	if (map->grid[(int)p->pos[Y]][(int)(p->pos[X] + plane[X] + offset[X])] <= 0)
		p->pos[X] += plane[X];
	if (plane[Y] > 0)
		offset[Y] = COLLISION_OFFSET;
	else
		offset[Y] = -COLLISION_OFFSET;
	if (map->grid[(int)(p->pos[Y] + plane[Y] + offset[Y])][(int)p->pos[X]] <= 0)
		p->pos[Y] += plane[Y];
}

void	rotate_direction(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir[X];
	old_plane_x = p->plane[X];
	p->dir[X] = p->dir[X] * cos(rot_speed) - p->dir[Y] * sin(rot_speed);
	p->dir[Y] = old_dir_x * sin(rot_speed) + p->dir[Y] * cos(rot_speed);
	p->plane[X] = p->plane[X] * cos(rot_speed) - p->plane[Y] * sin(rot_speed);
	p->plane[Y] = old_plane_x * sin(rot_speed) + p->plane[Y] * cos(rot_speed);
}
