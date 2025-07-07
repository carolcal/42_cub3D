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

static void	draw_3d_map(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game->player, &ray, x);
		dda(game, &ray);
		compute_line(&ray);
		draw_texture(game, &ray, x);
		draw_ceiling_and_floor(game, &ray, x);
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
