/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:14:09 by naharumi          #+#    #+#             */
/*   Updated: 2025/06/27 18:54:37 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	game_loop(t_game *game)
{
	handle_keys(game);
	render_img(game);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx->mlx_ptr, game_loop, game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx->mlx_ptr);
}
