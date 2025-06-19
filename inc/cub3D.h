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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/times.h>
# include "libft.h"

# define INVALID_MAP "Error: Invalid Map!\n"
# define INVALID_TEXTURE "Error: Invalid Texture!\n"
# define INVALID_COLOR "Error: Invalid Background Color!\n"

# define WIN_WIDTH 960
# define WIN_HEIGHT 512
# define TILE_SIZE 64

# define FOV 60.0
# define PI 3.14159265358979323846
# define MOVE_SPEED 0.1
# define ROT_SPEED  0.05

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

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

typedef struct	s_map
{
	int	textures[4];
	int	**grid;
	int	width;
	int	height;
}	t_map;

typedef struct	s_player
{
	char	initial_dir;	// 'N', 'S', 'E', 'W'
	double	pos[2];
	double	dir[2];
	double	plane[2];
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

typedef struct	s_game
{
	t_map		*map;
	t_player	*player;
	t_mlx 		*mlx;
}	t_game;

// Functions

//Init
t_game	*init(const char *map_file);

//Validate
int		validate_map_file(t_game *game, const char *map_file);
void	parse_map(t_game *game, int fd, char *line);
int		validate_player(t_player *player, int item, int x, int y);

// draw
void	init_mlx(t_game *game);
int		render_img(t_game *game);
int		close_window(t_game *game);
int		handle_keys(int key, t_game *game);

//Game
void	start_game(const char *map_file);

//Error
void	handle_error(char *error);

#endif