/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:17:26 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/25 17:17:26 by naharumi         ###   ########.fr       */
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

uint32_t	interpolate_color(uint32_t color1, uint32_t color2, double factor)
{
	uint8_t	rgb1[3];
	uint8_t	rgb2[3];
	uint8_t	rgb[3];

	rgb1[0] = (color1 >> 16) & 0xFF;
	rgb1[1] = (color1 >> 8) & 0xFF;
	rgb1[2] = color1 & 0xFF;
	rgb2[0] = (color2 >> 16) & 0xFF;
	rgb2[1] = (color2 >> 8) & 0xFF;
	rgb2[2] = color2 & 0xFF;
	rgb[0] = (uint8_t)(rgb1[0] + (rgb2[0] - rgb1[0]) * factor);
	rgb[1] = (uint8_t)(rgb1[1] + (rgb2[1] - rgb1[1]) * factor);
	rgb[2] = (uint8_t)(rgb1[2] + (rgb2[2] - rgb1[2]) * factor);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	draw_3d_map(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game->player, &ray, x);
		dda(game, &ray);
		compute_line(&ray);
		draw_ceiling_and_floor(game, &ray, x);
		draw_texture(game, &ray, x);
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
