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

void	init_ray(t_ray *ray, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->map_pos[0] = (int)player->pos[0];
	ray->map_pos[1] = (int)player->pos[1];
	ray->ray_dir[0] = player->dir[0] + player->plane[0] * ray->camera_x;
	ray->ray_dir[1] = player->dir[1] + player->plane[1] * ray->camera_x;
	ray->delta_dist[0] = fabs(1 / ray->ray_dir[0]);
	ray->delta_dist[1] = fabs(1 / ray->ray_dir[1]);
	if (ray->ray_dir[0] < 0)
	{
		ray->step[0] = -1;
		ray->side_dist[0] = (player->pos[0] - ray->map_pos[0])
			* ray->delta_dist[0];
	}
	else
	{
		ray->step[0] = 1;
		ray->side_dist[0] = (ray->map_pos[0] + 1 - player->pos[0])
			* ray->delta_dist[0];
	}
	if (ray->ray_dir[1] < 0)
	{
		ray->step[1] = -1;
		ray->side_dist[1] = (player->pos[1] - ray->map_pos[1])
			* ray->delta_dist[1];
	}
	else
	{
		ray->step[1] = 1;
		ray->side_dist[1] = (ray->map_pos[1] + 1 - player->pos[1])
			* ray->delta_dist[1];
	}
}

void	dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist[0] < ray->side_dist[1])
		{
			ray->side_dist[0] += ray->delta_dist[0];
			ray->map_pos[0] += ray->step[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[1] += ray->delta_dist[1];
			ray->map_pos[1] += ray->step[1];
			ray->side = 1;
		}
		if (game->map->grid[ray->map_pos[1]][ray->map_pos[0]] == 1)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->map_pos[0] - game->player->pos[0]
				+ (1 - ray->step[0]) / 2) / ray->ray_dir[0];
	else
		ray->wall_dist = (ray->map_pos[1] - game->player->pos[1]
				+ (1 - ray->step[1]) / 2) / ray->ray_dir[1];
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
		draw_line(game, x, &ray);
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
		WIN_WIDTH, WIN_HEIGHT, "Cub3D");
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
