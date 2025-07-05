/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:41:14 by marvin            #+#    #+#             */
/*   Updated: 2025/07/03 11:41:14 by marvin           ###   ########.fr       */
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

uint32_t	interpolate_color(uint32_t color1, uint32_t color2, double alpha)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (1 - alpha) * ((color1 >> 16) & 0xFF) + alpha * ((color2 >> 16) & 0xFF);
	g = (1 - alpha) * ((color1 >> 8) & 0xFF) + alpha * ((color2 >> 8) & 0xFF);
	b = (1 - alpha) * (color1 & 0xFF) + alpha * (color2 & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

static void	sort_sprites(t_sprite_order *order, int count)
{
	int				i;
	int				j;
	t_sprite_order	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (order[j].distance < order[j + 1].distance)
			{
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	order_sprites(t_game *game, t_sprite_order *order)
{
	int				i;
	double			dist[2];

	i = 0;
	while (i < game->num_sprites)
	{
		dist[X] = game->player->pos[X] - game->sprites[i].pos[X];
		dist[Y] = game->player->pos[Y] - game->sprites[i].pos[Y];
		order[i].index = i;
		order[i].distance = dist[X] * dist[X] + dist[Y] * dist[Y];
		i++;
	}
	sort_sprites(order, game->num_sprites);
}

void	draw_mini_sprites(t_game *g, int start_pos[2])
{
	int			i;
	int			color;
	int			screen[2];
	double		rel_pos[2];
	t_sprite	*s;

	i = 0;
	color = 0xFFFF00;
	while (i < g->num_sprites)
	{
		s = &g->sprites[i];
		if (s->enemy == true)
			color = 0xFF0000;
		rel_pos[X] = s->pos[X] - start_pos[X];
		rel_pos[Y] = s->pos[Y] - start_pos[Y];
		if (rel_pos[X] >= 0 && rel_pos[Y] >= 0
			&& rel_pos[X] < MINIMAP_WIDTH / (double)MINIMAP_TILE
			&& rel_pos[Y] < MINIMAP_HEIGHT / (double)MINIMAP_TILE)
		{
			screen[X] = MINIMAP_MARGIN + rel_pos[X] * MINIMAP_TILE;
			screen[Y] = MINIMAP_MARGIN + rel_pos[Y] * MINIMAP_TILE;
			draw_player_dot(g, (int []){screen[X], screen[Y]}, 2, color);
		}
		i++;
	}
}
