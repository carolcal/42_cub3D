/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/07/03 18:10:05 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_map_dimensions(t_map *map, const char *map_file)
{
	int		width;
	int		height;
	int		fd;
	char	*line;
	int		num_sprites; //BONUS

	height = 0;
	num_sprites = 0; //BONUS
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE, (char *)map_file);
	line = get_next_line(fd);
	while (line && !is_map_line(line))
		line = get_next_line(fd);
	while (line && is_map_line(line))
	{
		width = 0;
		while (line[width] && line[width] != '\n' && line[width] != '\r')
		{
			if (line[width] == 'P' || line[width] == 'G')
				num_sprites++;
			width++;
		}
		if (map->width <= width)
			map->width = width;
		line = get_next_line(fd);
		height++;
	}
	map->height = height;
	get_next_line(-42);
	close(fd);
	return (num_sprites);
}

static void	fill_grid(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->grid[y][x] = VOID;
			x++;
		}
		y++;
	}
}

static void	init_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = allocate_mem(sizeof(int *), map->height + 1);
	if (!map->grid)
		handle_error(MEMORY_ERROR, NULL);
	while (i < map->height)
	{
		map->grid[i] = allocate_mem(sizeof(int), map->width + 1);
		if (!map->grid[i])
			handle_error(MEMORY_ERROR, NULL);
		i++;
	}
	fill_grid(map);
}

static void	init_buttons(t_game *game)
{
	game->keys.w = false;
	game->keys.a = false;
	game->keys.s = false;
	game->keys.d = false;
	game->keys.left = false;
	game->keys.right = false;
	game->mouse_x = -1;			// BONUS
	game->mouse_pressed = 0;	// BONUS
}

static void	alloc_textures(t_game *game)
{
	int	i;

	game->enemy_tex_path[0] = ft_strdup(TEX_ENEMY0);
	game->enemy_tex_path[1] = ft_strdup(TEX_ENEMY1);
	game->enemy_tex_path[2] = ft_strdup(TEX_ENEMY2);
	game->enemy_tex_path[3] = ft_strdup(TEX_ENEMY3);
	game->goal_tex_path[0] = ft_strdup(TEX_GOAL0);
	game->goal_tex_path[1] = ft_strdup(TEX_GOAL1);
	game->goal_tex_path[2] = ft_strdup(TEX_GOAL2);
	game->goal_tex_path[3] = ft_strdup(TEX_GOAL3);
	i = 0;
	while (i < 5)	// 4 textures + 1 door texture
	{
		game->texture[i] = allocate_mem(1, sizeof(t_texture));
		game->enemy_texture[i] = allocate_mem(1, sizeof(t_texture));
		game->goal_texture[i] = allocate_mem(1, sizeof(t_texture));
		i++;
	}
}

t_game	*init(const char *map_file)
{
	t_game	*game;

	game = allocate_mem(1, sizeof(t_game));
	game->mlx = allocate_mem(1, sizeof(t_mlx));
	game->map = allocate_mem(1, sizeof(t_map));
	game->map->ceiling = 422;
	game->map->floor = 422;
	game->map->door_tex_path = ft_strdup(TEX_DOOR);						// BONUS
	game->player = allocate_mem(1, sizeof(t_player));
	game->player->player_num = 0;
	game->num_sprites = get_map_dimensions(game->map, map_file);		// BONUS
	game->sprites = allocate_mem(game->num_sprites, sizeof(t_sprite));	// BONUS
	game->map->parsed_sprites = 0;										// BONUS
	alloc_textures(game);
	init_buttons(game);
	init_grid(game->map);
	return (game);
}
