/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/17 17:36:19 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

t_game  *init(const char *map_file)
{
    t_game *game;

    (void) map_file;
    game = allocate_mem(1, sizeof(t_game));
    game->map = allocate_mem(1, sizeof(t_map));
    game->map->texture = allocate_mem(1, sizeof(t_texture));
    game->player = allocate_mem(1, sizeof(t_player));
    game->mlx = allocate_mem(1, sizeof(t_mlx));
    
    return (game);
}