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

# include "../minilibx-linux/mlx.h" // # include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <string.h>
# include <math.h>
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

# define WIN_WIDTH 960
# define WIN_HEIGHT 512
# define TILE_SIZE 64

# define FOV 60.0
# define MOVE_SPEED 0.05
# define ROT_SPEED  0.05
# define COLLISION_OFFSET 0.5

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364
# define ESC_KEY 65307
# define SPACE_KEY

enum	e_axis
{
	X,
	Y
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

typedef struct s_ray
{
	double	camera_x;
	double	wall_dist;
	double	ray_dir[2];
	double	delta_dist[2];
	double	side_dist[2];
	int		map_pos[2];
	int		step[2];
	int		hit;
	int		side;
	int		line_height;
	int		line_start;
	int		line_end;
}	t_ray;

typedef struct s_texture {
	void	*tex_ptr;
	char	*tex_addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

enum	e_map_elements
{
	EMPTY = 0,
	WALL = 1,
	VOID = 2,
};

typedef struct	s_map
{
	char		*tex_path[4];
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
	double	plane[2];
	int		player_num;
}	t_player;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct	s_game
{
	t_map		*map;
	t_player	*player;
	t_mlx 		*mlx;
	t_texture	*texture[4];
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

// draw
void	init_mlx(t_game *game);
int		render_img(t_game *game);
int		close_window(t_game *game);
int		handle_keys(int key, t_game *game);

//Game
void	start_game(const char *map_file);

//Error
void	handle_error(char *error, char *str);

#endif