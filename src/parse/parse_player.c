/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:45:08 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/18 16:39:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_player(t_player *player, int item, int x, int y)
{
	if(player->pos[0])
		return (0);
	if (!ft_strchr("NSWE", item))
		return (0);
	player->pos[0] = x;
	player->pos[1] = y;
	if (item == 'N' || item == 'S')
	{
		player->dir[0] = NORTH_SOUTH;
		if (item == 'N')
			player->dir[1] = LEFT;
		else
			player->dir[1] = RIGHT;
	}
	else
	{
		player->dir[0] = WEST_EAST;
		if (item == 'W')
			player->dir[1] = LEFT;
		else
			player->dir[1] = RIGHT;
	}
	return (1);
}