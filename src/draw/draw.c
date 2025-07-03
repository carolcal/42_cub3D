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

static void	draw_minimap(t_game *g)
{
	int		start_pos[2];
	int		dot_pos[2];
	int		end_pos[2];
	double	rel_pos[2];
	double	player_angle;

	draw_minimap_bg(g);
	start_pos[X] = (int)(g->player->pos[X]
			- (MINIMAP_WIDTH / (2.0 * MINIMAP_TILE)));
	start_pos[Y] = (int)(g->player->pos[Y]
			- (MINIMAP_HEIGHT / (2.0 * MINIMAP_TILE)));
	draw_minimap_tiles(g, start_pos);
	rel_pos[X] = g->player->pos[X] - start_pos[X];
	rel_pos[Y] = g->player->pos[Y] - start_pos[Y];
	dot_pos[X] = MINIMAP_MARGIN + rel_pos[X] * MINIMAP_TILE;
	dot_pos[Y] = MINIMAP_MARGIN + rel_pos[Y] * MINIMAP_TILE;
	draw_player_dot(g, dot_pos, 2, 0xFF0000);
	player_angle = atan2(g->player->dir[Y], g->player->dir[X]);
	end_pos[X] = dot_pos[X] + cos(player_angle) * 5;
	end_pos[Y] = dot_pos[Y] + sin(player_angle) * 5;
	draw_player_line(g, dot_pos, end_pos, 0xFF0000);
}

int	render_img(t_game *game)
{
	ft_bzero(game->mlx->img_addr, WIN_WIDTH * WIN_HEIGHT
		* (game->mlx->bpp / 8));
	draw_3d_map(game);
	// draw_sprites(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img_ptr, 0, 0);
	return (0);
}
