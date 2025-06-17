/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/17 10:28:18 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

// t_map *init_map(const char *map_file)
// {
//     t_map *map;
    
//     map = allocate_mem(1, sizeof(t_map));
//     return (map);
// }
// t_player *init_player()

t_game  *init(const char *map_file)
{
    t_game *game;

    (void) map_file;
    game = allocate_mem(1, sizeof(t_game));
    game->map = allocate_mem(1, sizeof(t_map));
    game->player = allocate_mem(1, sizeof(t_player));
    game->mlx = allocate_mem(1, sizeof(t_mlx));
    
    return (game);
}