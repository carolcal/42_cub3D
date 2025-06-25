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
# include <stdbool.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <string.h>
// # include <math.h>
// # include <sys/time.h>
# include "libft.h"

# define EMPTY_FILE "Error: Empty File"
# define INVALID_FORMAT "Error: Invalid Format File"
# define INVALID_FILE "Error: Invalid File"
# define INVALID_LINE "Error: Invalid Line"
# define INVALID_MAP "Error: Invalid Map"
# define INVALID_PLAYER "Error: Invalid Player Position"
# define INVALID_TEXTURE "Error: Invalid Texture"
# define INVALID_COLOR "Error: Invalid Background Color"
# define MEMORY_ERROR "Error: When using malloc"
# define DUPLICATE_TEXTURE "Error: Duplicate Texture"
# define DUPLICATE_PLAYER "Error: Duplicate Player on the Map"
# define MISSING_TEXTURE "Error: Missing one or more Textures"
# define MISSING_COLOR "Error: Missing one or more Colors"
# define MISSING_MAP "Error: Missing Map in File"
# define MISSING_PLAYER "Error: Missing Player in Map"

enum	e_coordinates
{
	X = 0,
	Y = 1
};

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

enum	e_map_elements
{
	EMPTY = 0,
	WALL = 1,
	VOID = 2,
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
	double	pos[2];
	double	dir[2];
	int		player_num;
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
bool 	is_valid_line(char *line);
bool 	is_texture_line(char *line);
bool 	is_color_line(char *line);
bool 	is_map_line(char *line);
bool 	is_empty_line(char *line);
void    parse_textures(t_map *map, char *line);
void    parse_color(t_map *map, char *line);
void	parse_map(t_game *game, int fd, char *line);
void	parse_player(t_player *player, char c, int x, int y);
void	parse_file(t_game *game, const char *map_file);

//Validdation
bool 	is_void_or_wall(int curr);
bool	is_empty_or_wall(int curr);
bool	check_around_space(t_map *map, int y, int x);
void	validate_textures(char *texture[4]);
void	validate_colors(t_map *map);
void	validate_map(t_game *game);
void	validate_player(t_game *game);
void	validate(t_game *game);

//Game
void	start_game(const char *map_file);

//Error
void	handle_error(char *error, char *str);

#endif