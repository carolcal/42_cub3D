/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:32:25 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 10:35:07 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_side_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (player->pos[X] - ray->map_pos[X])
			* ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (ray->map_pos[X] + 1 - player->pos[X])
			* ray->delta_dist[X];
	}
	if (ray->ray_dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (player->pos[Y] - ray->map_pos[Y])
			* ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (ray->map_pos[Y] + 1 - player->pos[Y])
			* ray->delta_dist[Y];
	}
}

void	init_ray(t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->map_pos[X] = (int)player->pos[X];
	ray->map_pos[Y] = (int)player->pos[Y];
	ray->ray_dir[X] = player->dir[X] + player->plane[X] * ray->camera_x;
	ray->ray_dir[Y] = player->dir[Y] + player->plane[Y] * ray->camera_x;
	if (ray->ray_dir[X] == 0)
		ray->delta_dist[X] = 1e30;
	else
		ray->delta_dist[X] = fabs(1 / ray->ray_dir[X]);
	if (ray->ray_dir[Y] == 0)
		ray->delta_dist[Y] = 1e30;
	else
		ray->delta_dist[Y] = fabs(1 / ray->ray_dir[Y]);
	init_side_step(ray, player);
}

void	dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map_pos[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map_pos[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (game->map->grid[ray->map_pos[Y]][ray->map_pos[X]] > EMPTY)
			ray->hit = game->map->grid[ray->map_pos[Y]][ray->map_pos[X]];
	}
}

void	compute_line(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->line_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->line_end >= WIN_HEIGHT)
		ray->line_end = WIN_HEIGHT - 1;
}
