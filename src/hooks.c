/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:10:32 by marvin            #+#    #+#             */
/*   Updated: 2025/06/18 21:10:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward_backward(t_player *p, t_map *map, int key)
{
	if (key == W_KEY)
	{
		if (map->grid[(int)(p->pos[1])][(int)(p->pos[0] + p->dir[0] * MOVE_SPEED)] == 0)
			p->pos[0] += p->dir[0] * MOVE_SPEED;
		if (map->grid[(int)(p->pos[1] + p->dir[1] * MOVE_SPEED)][(int)(p->pos[0])] == 0)
			p->pos[1] += p->dir[1] * MOVE_SPEED;
	}
	if (key == S_KEY)
	{
		if (map->grid[(int)(p->pos[1])][(int)(p->pos[0] - p->dir[0] * MOVE_SPEED)] == 0)
			p->pos[0] -= p->dir[0] * MOVE_SPEED;
		if (map->grid[(int)(p->pos[1] - p->dir[1] * MOVE_SPEED)][(int)(p->pos[0])] == 0)
			p->pos[1] -= p->dir[1] * MOVE_SPEED;
	}
}

void	move_left_right(t_player *p, t_map *map, int key)
{
	double	perp_x ;
	double	perp_y;

	if (key == A_KEY)
	{
		perp_x = p->dir[1];
		perp_y = -p->dir[0];
		if (map->grid[(int)(p->pos[1])][(int)(p->pos[0] + perp_x * MOVE_SPEED)] == 0)
			p->pos[0] += perp_x * MOVE_SPEED;
		if (map->grid[(int)(p->pos[1] + perp_y * MOVE_SPEED)][(int)(p->pos[0])] == 0)
			p->pos[1] += perp_y * MOVE_SPEED;
	}
	if (key == D_KEY)
	{
		perp_x = -p->dir[1];
		perp_y = p->dir[0];
		if (map->grid[(int)(p->pos[1])][(int)(p->pos[0] + perp_x * MOVE_SPEED)] == 0)
			p->pos[0] += perp_x * MOVE_SPEED;
		if (map->grid[(int)(p->pos[1] + perp_y * MOVE_SPEED)][(int)(p->pos[0])] == 0)
			p->pos[1] += perp_y * MOVE_SPEED;
	}
}

void	rotate_direction(t_player *p, int key)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == LEFT_KEY)
	{
		old_dir_x = p->dir[0];
		old_plane_x = p->plane[0];
		p->dir[0] = p->dir[0] * cos(-ROT_SPEED) - p->dir[1] * sin(-ROT_SPEED);
		p->dir[1] = old_dir_x * sin(-ROT_SPEED) + p->dir[1] * cos(-ROT_SPEED);
		p->plane[0] = p->plane[0] * cos(-ROT_SPEED) - p->plane[1] * sin(-ROT_SPEED);
		p->plane[1] = old_plane_x * sin(-ROT_SPEED) + p->plane[1] * cos(-ROT_SPEED);
	}
	if (key == RIGHT_KEY)
	{
		old_dir_x = p->dir[0];
		old_plane_x = p->plane[0];
		p->dir[0] = p->dir[0] * cos(ROT_SPEED) - p->dir[1] * sin(ROT_SPEED);
		p->dir[1] = old_dir_x * sin(ROT_SPEED) + p->dir[1] * cos(ROT_SPEED);
		p->plane[0] = p->plane[0] * cos(ROT_SPEED) - p->plane[1] * sin(ROT_SPEED);
		p->plane[1] = old_plane_x * sin(ROT_SPEED) + p->plane[1] * cos(ROT_SPEED);
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
