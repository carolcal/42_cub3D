/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:06:43 by naharumi          #+#    #+#             */
/*   Updated: 2025/07/03 09:06:43 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_minimap_bg(t_game *g)
{
	int	x;
	int	y;
	int	screen[2];
	int	bg_color;
	int	translucent;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			screen[X] = MINIMAP_MARGIN + x;
			screen[Y] = MINIMAP_MARGIN + y;
			bg_color = *(int *)(g->mlx->img_addr + screen[Y] * g->mlx->size_line
					+ screen[X] * (g->mlx->bpp / 8));
			translucent = interpolate_color(bg_color, 0x202020, 0.5);
			put_pixel(g, screen[X], screen[Y], translucent);
			x++;
		}
		y++;
	}
}

static void	draw_square(t_game *g, int pos[2], int map_pos[2])
{
	int	i;
	int	j;
	int	color;

	if (g->map->grid[map_pos[Y]][map_pos[X]] == WALL)
		color = 0x888888;
	if (g->map->grid[map_pos[Y]][map_pos[X]] == DOOR_CLOSE)
		color = 0x4444FF;
	i = 0;
	while (i < MINIMAP_TILE - 1)
	{
		j = 0;
		while (j < MINIMAP_TILE - 1)
		{
			put_pixel(g, pos[X] + j, pos[Y] + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_tiles(t_game *g, int start_pos[2])
{
	int	pos[2];
	int	map_pos[2];
	int	screen_pos[2];

	pos[Y] = 0;
	while (pos[Y] < MINIMAP_HEIGHT / MINIMAP_TILE)
	{
		pos[X] = 0;
		while (pos[X] < MINIMAP_WIDTH / MINIMAP_TILE)
		{
			map_pos[X] = start_pos[X] + pos[X];
			map_pos[Y] = start_pos[Y] + pos[Y];
			screen_pos[X] = MINIMAP_MARGIN + pos[X] * MINIMAP_TILE;
			screen_pos[Y] = MINIMAP_MARGIN + pos[Y] * MINIMAP_TILE;
			if (map_pos[X] >= 0 && map_pos[X] < g->map->width
				&& map_pos[Y] >= 0 && map_pos[Y] < g->map->height)
			{
				if (g->map->grid[map_pos[Y]][map_pos[X]] == WALL
					|| g->map->grid[map_pos[Y]][map_pos[X]] == DOOR_CLOSE)
					draw_square(g, screen_pos, map_pos);
			}
			pos[X]++;
		}
		pos[Y]++;
	}
}

void	draw_player_dot(t_game *g, int dot_pos[2], int radius, int color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(g, dot_pos[X] + x, dot_pos[Y] + y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_line(t_game *g, int start[2], int end[2], int color)
{
	int		i;
	double	steps;
	double	pos[2];
	double	delta[2];
	double	increment[2];

	delta[X] = end[X] - start[X];
	delta[Y] = end[Y] - start[Y];
	if (fabs(delta[X]) > fabs(delta[Y]))
		steps = fabs(delta[X]);
	else
		steps = fabs(delta[Y]);
	increment[X] = delta[X] / steps;
	increment[Y] = delta[Y] / steps;
	pos[X] = start[X];
	pos[Y] = start[Y];
	i = 0;
	while (i <= steps)
	{
		put_pixel(g, round(pos[X]), round(pos[Y]), color);
		pos[X] += increment[X];
		pos[Y] += increment[Y];
		i++;
	}
}
