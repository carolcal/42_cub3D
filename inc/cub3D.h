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

# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <string.h>
// # include <math.h>
// # include <sys/time.h>
# include "libft.h"

# define INVALID_FILE "Error: Invalid File!\n"
# define INVALID_MAP "Error: Invalid Map!\n"
# define INVALID_TEXTURE "Error: Invalid Texture!\n"
# define INVALID_COLOR "Error: Invalid Background Color!\n"
# define MEMORY_ERROR "Error: When using malloc.\n"

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
	char		*texture[4];
	int			**grid;
	int			width;
	int			height;
	uint32_t	ceiling;
	uint32_t	floor;
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

//Parse
void	parse_map_file(t_game *game, const char *map_file);
int		empty_line(char *line);
int 	is_space_or_one(char c);
int		line_len(char *str);
void	parse_map(t_game *game, int fd, char *line);
int		parse_player(t_player *player, int item, int x, int y);
void    parse_property(t_map *map, char *line);
void    parse_color(t_map *map, char *line);

//Game
void	start_game(const char *map_file);

//Error
void	handle_error(char *error);

#endif