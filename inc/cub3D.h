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
# include "libft.h"

# define INVALID_MAP "Error: Invalid Map!\n"
# define INVALID_TEXTURE "Error: Invalid Texture!\n"
# define INVALID_COLOR "Error: Invalid Background Color!\n"

enum	e_direction
{
	RIGHT = 1,
	LEFT = -1
};

enum	e_side
{
	NORTH_SOUTH,
	WEST_EAST
};


enum	e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct	s_map
{
	int textures[4];
	int	**grid;
	int	width;
	int	height;
}	t_map;

typedef struct	s_player
{
	double pos[2];
	double dir[2];
}	t_player;

typedef struct	s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int width;
	int height;
	char *img_data;
}	t_mlx;

typedef struct	s_game
{
	t_map *map;
	t_player *player;
	t_mlx *mlx;
}	t_game;

// Functions

//Init
t_game	*init(const char *map_file);

//Validate
int		validate_map_file(t_game *game, const char *map_file);
void	parse_map(t_game *game, int fd, char *line);
int		validate_player(t_player *player, int item, int x, int y);

//Game
void	start_game(const char *map_file);

//Error
void	handle_error(char *error);

#endif