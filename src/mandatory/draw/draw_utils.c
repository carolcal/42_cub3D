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
