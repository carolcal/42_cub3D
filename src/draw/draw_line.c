/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:29:04 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 15:41:18 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir[X] > 0)
			return (game->texture[EAST]);
		return (game->texture[WEST]);
	}
	else
	{
		if (ray->ray_dir[Y] > 0)
			return (game->texture[SOUTH]);
		return (game->texture[NORTH]);
	}
}

static int	calc_tex_x(t_player *p, t_ray *r, t_texture *t)
{
	int		tex_x;
	double	wall_x;

	if (r->side == 0)
		wall_x = p->pos[Y] + r->wall_dist * r->ray_dir[Y];
	else
		wall_x = p->pos[X] + r->wall_dist * r->ray_dir[X];
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * t->width);
	if ((r->side == 0 && r->ray_dir[X] > 0)
		|| (r->side == 1 && r->ray_dir[Y] < 0))
		tex_x = t->width - tex_x - 1;
	return (tex_x);
}

static void	draw_textured_line(t_game *g, t_ray *r, t_texture *t, int x)
{
	int		y;
	int		tex[2];
	int		color;
	double	step;
	double	tex_pos;

	tex[X] = calc_tex_x(g->player, r, t);
	step = 1.0 * t->height / r->line_height;
	tex_pos = (r->line_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	y = r->line_start;
	while (y < r->line_end)
	{
		tex[Y] = (int)tex_pos & (t->height - 1);
		tex_pos += step;
		color = *(int *)(t->tex_addr + tex[Y] * t->size_line
				+ tex[X] * (t->bpp / 8));
		put_pixel(g, x, y, color);
		y++;
	}
}

void	draw_texture(t_game *game, t_ray *ray, int x)
{
	t_texture	*tex;

	tex = get_wall_texture(game, ray);
	draw_textured_line(game, ray, tex, x);
}

void	draw_ceiling_and_floor(t_game *game, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;
	double		factor;
	double		current_dist;

	y = 0;
	while (y < ray->line_start)
	{
		current_dist = WIN_HEIGHT / (WIN_HEIGHT - 2.0 * y);
		factor = 1.0 - (1.0 / (1.0 + current_dist / 5.0));
		color = interpolate_color(game->map->ceiling, 0x000000, factor);
		put_pixel(game, x, y, color);
		y++;
	}
	y = ray->line_end;
	while (y < WIN_HEIGHT)
	{
		current_dist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		factor = 1.0 - (1.0 / (1.0 + current_dist / 5.0));
		color = interpolate_color(game->map->floor, 0x000000, factor);
		put_pixel(game, x, y, color);
		y++;
	}
}
