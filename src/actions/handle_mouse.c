/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:17:01 by marvin            #+#    #+#             */
/*   Updated: 2025/07/02 21:17:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		game->mouse_pressed = 1;
		game->mouse_x = x;
	}
	(void)y;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	if (button == 1)
		game->mouse_pressed = 0;
	(void)x;
	(void)y;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;

	(void)y;
	if (!game->mouse_pressed)
		return (0);
	delta_x = x - game->mouse_x;
	if (delta_x != 0)
		rotate_direction(game->player, delta_x * MOUSE_SENSITIVITY);
	game->mouse_x = x;
	return (0);
}
