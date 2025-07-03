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
	double	inv_det;

	position[X] = sprite->pos[X] - player->pos[X];
	position[Y] = sprite->pos[Y] - player->pos[Y];
	inv_det = 1.0 / (player->plane[X] * player->dir[Y] - player->dir[X] * player->plane[Y]);
	sprite->transform[X] = inv_det * (player->dir[Y] * position[X] - player->dir[X] * position[Y]);
	sprite->transform[Y] = inv_det * (-player->plane[Y] * position[X] + player->plane[X] * position[Y]);
	if (sprite->transform[Y] <= 0.01)
		return (false);
	return (true);	
}

static void	get_sprite_coordinates(t_sprite *sprite)
{
	sprite->screen_x = (int)((WIN_WIDTH / 2) * (1 + sprite->transform[X] / sprite->transform[Y]));
	sprite->height = abs((int)(WIN_HEIGHT / sprite->transform[Y]));
	sprite->draw_start[Y] = -sprite->height / 2 + WIN_HEIGHT / 2;
	if (sprite->draw_start[Y] < 0) 
		sprite->draw_start[Y] = 0;
	sprite->draw_end[Y] = sprite->height / 2 + WIN_HEIGHT / 2;
	if (sprite->draw_end[Y] >= WIN_HEIGHT) 
		sprite->draw_end[Y] = WIN_HEIGHT - 1;
	sprite->width = abs((int)(WIN_HEIGHT / sprite->transform[Y]));
	sprite->draw_start[X] = -sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_start[X] < 0) 
		sprite->draw_start[X] = 0;
	sprite->draw_end[X] = sprite->width / 2 + sprite->screen_x;
	if (sprite->draw_end[X] >= WIN_WIDTH) 
		sprite->draw_end[X] = WIN_WIDTH - 1;

}
static void draw_sprite_y(t_game *game, t_sprite *sprite, int x, int tex_x)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = sprite->draw_start[Y];
	while (y < sprite->draw_end[Y])
	{
		d = y * 256 - WIN_HEIGHT * 128 + sprite->height * 128;
		tex_y = (d * game->sprite_texture[0]->height) / sprite->height / 256;

		color = *(int *)(game->sprite_texture[0]->tex_addr +
			tex_y * game->sprite_texture[0]->size_line +
			tex_x * (game->sprite_texture[0]->bpp / 8));
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(game, x, y, color);
		y++;
	}
}

static void draw_sprite_x(t_game *game, t_sprite *sprite)
{
	int	x;
	int	tex_x;

	x = sprite->draw_start[X];
	while (x < sprite->draw_end[X])
	{
		tex_x = (int)((x - (-sprite->width / 2 + sprite->screen_x)) * 
			game->sprite_texture[0]->width / sprite->width);

		if (x > 0 && x < WIN_WIDTH)
		{
			if (sprite->transform[Y] > 0 && sprite->transform[Y] < 1)
				sprite->transform[Y] = 1;
			if (sprite->transform[Y] < game->z_buffer[x])
				draw_sprite_y(game, sprite, x, tex_x);
		}
		x++;
	}
}


void    draw_sprites(t_game *game)
{
    int i;

    i = 0;
    while (i < game->num_sprites)
    {
		if (!get_sprite_position(&game->sprites[i], game->player))
		{
			i++;
			continue;
		}
		get_sprite_coordinates(&game->sprites[i]);
		draw_sprite_x(game, &game->sprites[i]);
        i++;
    }
}