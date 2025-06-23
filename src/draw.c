/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:24:33 by marvin            #+#    #+#             */
/*   Updated: 2025/06/18 17:24:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = game->mlx->img_addr + (y * game->mlx->size_line
			+ x * (game->mlx->bpp / 8));
	*(unsigned int *)pixel = color;
}

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
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

void	draw_textured_line(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex = get_wall_texture(game, ray);
	double		wall_x;
	int			tex_x, tex_y;
	double		step;
	double		tex_pos;
	int			y;

	// encontrar posição x na textura
	if (ray->side == 0)
		wall_x = game->player->pos[1] + ray->wall_dist * ray->ray_dir[1];
	else
		wall_x = game->player->pos[0] + ray->wall_dist * ray->ray_dir[0];
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir[0] > 0) ||
		(ray->side == 1 && ray->ray_dir[1] < 0))
		tex_x = tex->width - tex_x - 1;

	// configurar step e tex_pos
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->line_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

	y = ray->line_start;
	while (y < ray->line_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		int color = *(int *)(tex->tex_addr + tex_y * tex->size_line + tex_x * (tex->bpp / 8));
		put_pixel(game, x, y, color);
		y++;
	}
}

void	init_ray(t_ray *ray, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->map_pos[X] = (int)player->pos[X];
	ray->map_pos[Y] = (int)player->pos[Y];
	ray->ray_dir[X] = player->dir[X] + player->plane[X] * ray->camera_x;
	ray->ray_dir[Y] = player->dir[Y] + player->plane[Y] * ray->camera_x;
	ray->delta_dist[X] = fabs(1 / ray->ray_dir[X]);
	ray->delta_dist[Y] = fabs(1 / ray->ray_dir[Y]);
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

void	dda(t_ray *ray, t_game *game)
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
		if (game->map->grid[ray->map_pos[Y]][ray->map_pos[X]] == 1)
			ray->hit = 1;
		if (ray->side == 0)
			ray->wall_dist = (ray->map_pos[X] - game->player->pos[X]
					+ (1 - ray->step[X]) / 2) / ray->ray_dir[X];
		else
			ray->wall_dist = (ray->map_pos[Y] - game->player->pos[Y]
					+ (1 - ray->step[Y]) / 2) / ray->ray_dir[Y];
	}
}

void	compute_line(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->line_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->line_end >= WIN_HEIGHT)
		ray->line_end = WIN_HEIGHT - 1;
}

/*
void	draw_line(t_game *game, int x, t_ray *ray)
{
	int	y = ray->line_start;
	int	color = (ray->side == 1) ? 0xAAAAAA : 0xFFFFFF;

	while (y < ray->line_end)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}
*/

void	draw_3d_map(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, x, game->player);
		dda(&ray, game);
		compute_line(&ray);
		draw_textured_line(game, x, &ray);
		x++;
	}
}

int	render_img(t_game *game)
{
	ft_bzero(game->mlx->img_addr, WIN_WIDTH * WIN_HEIGHT
		* (game->mlx->bpp / 8));
	draw_3d_map(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img_ptr, 0, 0);
	return (0);
}

void	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		handle_error("Error: Failed to initialize MLX.\n");
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx->win_ptr)
		handle_error("Error: Failed to create MLX window.\n");
	game->mlx->img_ptr = mlx_new_image(game->mlx->mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx->img_ptr)
		handle_error("Error: Failed to create image.\n");
	game->mlx->img_addr = mlx_get_data_addr(game->mlx->img_ptr,
		&game->mlx->bpp, &game->mlx->size_line, &game->mlx->endian);
	if (!game->mlx->img_addr)
		handle_error("Error: Failed to get image address.\n");
	return ;
}

int	close_window(t_game *game)
{
	if (game->mlx->img_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img_ptr);
	if (game->mlx->win_ptr)
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	if (game->mlx->mlx_ptr)
		mlx_destroy_display(game->mlx->mlx_ptr);
	clear_mem();
	exit(EXIT_SUCCESS);
	return (0);
}
