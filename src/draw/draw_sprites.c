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

#include "cub3D.h"

static bool get_sprite_position(t_sprite *sprite, t_player *player)
{
	double	position[2];
	double inv_det;

	position[X] = sprite->pos[X] - player->pos[X];
	position[Y] = sprite->pos[Y] - player->pos[Y];
	inv_det = 1.0 / (player->plane[X] * player->dir[Y] - player->dir[X] * player->plane[Y]);
	sprite->transform[X] = inv_det * (player->dir[Y] * position[X] - player->dir[X] * position[Y]);
	sprite->transform[Y] = inv_det * (-player->plane[Y] * position[X] + player->plane[X] * position[Y]);
	if (sprite->transform[Y] <= 0.01)
		return (false);
	sprite->screen_x = (int)((WIN_WIDTH / 2) * (1 + sprite->transform[X] / sprite->transform[Y]));
	sprite->height = abs((int)(WIN_HEIGHT / sprite->transform[Y]));
	sprite->draw_start[Y] = -sprite->height / 2 + WIN_HEIGHT / 2;
	if (sprite->draw_start[Y] < 0) 
		sprite->draw_start[Y] = 0;
	sprite->draw_end[Y] = sprite->height / 2 + WIN_HEIGHT / 2;
	if (sprite->draw_end[Y] >= WIN_HEIGHT) 
		sprite->draw_end[Y] = WIN_HEIGHT - 1;
	sprite->width = abs((int)(WIN_HEIGHT / sprite->transform[Y]));
		sprite->draw_end[X] = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end[X] < 0) 
		sprite->draw_end[X] = 0;
	sprite->draw_end[Y] = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end[Y] >= WIN_WIDTH) 
		sprite->draw_end[Y] = WIN_WIDTH - 1;
	return (true);	
}


void    draw_sprites(t_game *game)
{
    int i;

    i = 0;
	printf("draw sprites\n");
    while (i < game->num_sprites)
    {
		if (!get_sprite_position(&game->sprites[i], game->player))
		{
			i++;
			continue;
		}
		printf("pegou posições!\n");
		//DESENHAR SPRITE USANDO TEXTURA
		/* for (int stripe = game->sprites[i].draw_end[X]; stripe < game->sprites[i].draw_end[Y]; stripe++)
		{
			int tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) * 
				game->sprite_texture[0]->width / sprite_width);

			if (stripe > 0 && stripe < WIN_WIDTH && transform_y < game->z_buffer[stripe])
			{
				// 6. Desenhar linha por linha da textura
				for (int y = game->sprites[i].draw_start[Y]; y < game->sprites[i].draw_end[Y]; y++)
				{
					int d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
					int tex_y = (d * game->sprite_texture[0]->height) / sprite_height / 256;

					int color = *(int *)(game->sprite_texture[0]->tex_addr +
						tex_y * game->sprite_texture[0]->size_line +
						tex_x * (game->sprite_texture[0]->bpp / 8));

					if ((color & 0x00FFFFFF) != 0)
						put_pixel(game, stripe, y, color);
				}
			}
		} */

        i++;
    }
}