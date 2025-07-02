/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:54:32 by marvin            #+#    #+#             */
/*   Updated: 2025/07/02 11:54:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

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

void    draw_sprites(t_game *game, t_ray *ray, int x)
{
    int i;

    i = 0;
    while (i < num_sprites)
    {
		// 1. Posição relativa ao jogador
		double sprite_x = sprite[i].pos[X] - player->pos[X];
		double sprite_y = sprite[i].pos[Y] - player->pos[Y];

		// 2. Inverso da matriz de câmera (para transformar coordenadas)
		double inv_det = 1.0 / (player->plane[X] * player->dir[Y] - player->dir[X] * player->plane[Y]);
		double transform_x = inv_det * (game->player->dir[Y] * sprite_x - game->player->dir[X] * sprite_y);
		double transform_y = inv_det * (-game->player->plane[Y] * sprite_x + game->player->plane[X] * sprite_y);

		// 3. Posição na tela
		int sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));

		// 4. Dimensões
		int sprite_height = abs((int)(WIN_HEIGHT / transform_y));
		int draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
		int draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;

		int sprite_width = abs((int)(WIN_HEIGHT / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;

		//DESENHAR SPRITE USANDO TEXTURA
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			// Cálculo do tex_x: a coluna da textura correspondente à tela
			int tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) 
							* texture->width / sprite_width);

			// Verifica se está visível e na frente da parede
			if (transform_y > 0 && stripe >= 0 && stripe < WIN_WIDTH
				&& transform_y < z_buffer[stripe])
			{
				// Agora desenha verticalmente (de cima para baixo)
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
					int tex_y = (d * texture->height) / sprite_height / 256;

					// Pega o pixel da textura
					int color = *(int *)(texture->tex_addr 
						+ tex_y * texture->size_line 
						+ tex_x * (texture->bpp / 8));

					// Verifica transparência (geralmente 0 é transparente)
					if ((color & 0x00FFFFFF) != 0)
						put_pixel(game, stripe, y, color);
				}
			}
		}
		if (frame % 10 == 0)
			sprite[i].texture_id = (sprite[i].texture_id + 1) % NUM_FRAMES;

        i++;
    }
}