/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:07:37 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/03 14:55:51 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_colision_x(t_sprite *sprite, double next[2], t_map *map)
{
	int		coord[2];
	double	test_x;

	test_x = next[X] + sprite->dir[X] * sprite->radius;
	if (test_x >= 0 && test_x < map->width)
		coord[X] = (int)test_x;
	else
		coord[X] = (int)sprite->pos[X];
	coord[Y] = (int)(sprite->pos[Y]);
	if (coord[X] >= 0 && coord[X] < map->width
		&& coord[Y] >= 0 && coord[Y] < map->height)
	{
		if (map->grid[coord[Y]][coord[X]] == 0)
			sprite->pos[X] = next[X];
		else
			sprite->dir[X] *= -1;
	}
}

void	check_colision_y(t_sprite *sprite, double next[2], t_map *map)
{
	int		coord[2];
	double	test_y;

	test_y = next[Y] + sprite->dir[Y] * sprite->radius;
	if (test_y >= 0 && test_y < map->height)
		coord[Y] = (int)test_y;
	else
		coord[Y] = (int)sprite->pos[Y];
	coord[X] = (int)(sprite->pos[X]);
	if (coord[X] >= 0 && coord[X] < map->width
		&& coord[Y] >= 0 && coord[Y] < map->height)
	{
		if (map->grid[coord[Y]][coord[X]] == 0)
			sprite->pos[Y] = next[Y];
		else
			sprite->dir[Y] *= -1;
	}
}

void	update_sprites(t_game *game)
{
	t_sprite	*sprite;
	double		next[2];
	double		speed;
	int			i;

	if (!game || !game->sprites || !game->map || !game->map->grid)
		return ;
	i = 0;
	speed = 0.005;
	while (i < game->num_sprites)
	{
		sprite = &game->sprites[i];
		if (sprite->enemy == false)
		{
			i++;
			continue;
		}
		next[X] = sprite->pos[X] + sprite->dir[X] * speed;
		next[Y] = sprite->pos[Y] + sprite->dir[Y] * speed;
		check_colision_x(sprite, next, game->map);
		check_colision_y(sprite, next, game->map);
		i++;
	}
}

int	player_touch_sprite(t_game *game)
{
	int		i;
	double	d[2];
	double	distance;
	double	collision_radius;

	i = 0;
	while (i < game->num_sprites)
	{
		d[X] = game->player->pos[X] - game->sprites[i].pos[X];
		d[Y] = game->player->pos[Y] - game->sprites[i].pos[Y];
		distance = sqrt(d[X] * d[X] + d[Y] * d[Y]);
		collision_radius = 1;
		if (distance < collision_radius)
		{
			if (game->sprites[i].enemy)
				return (1);
			else
				return (2);
		}
		i++;
	}
	return (0);
}
