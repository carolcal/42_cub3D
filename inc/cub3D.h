/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:51 by marvin            #+#    #+#             */
/*   Updated: 2025/06/12 16:30:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/times.h>

enum e_direction
{
    RIGHT = 1;
    LEFT = -1,
}

enum    e_texture
{
    NORTH,
    SOUTH,
    WEST,
    EAST
}

typedef struct s_map
{
    int textures[4];

} t_map;

typedef struct s_player
{
    double pos[2];
    double dir[2];
} t_player;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int width;
    int height;
    char *img_data;
} t_mlx;

typedef struct s_game
{
    t_map map;
    t_player player;
    t_mlx mlx;
} t_game;

#endif