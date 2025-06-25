/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/25 19:40:44 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"



void    parse_file(t_game *game, const char *map_file)
{
	int     fd;
	char    *line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE, (char *)map_file);
	line = get_next_line(fd);
	if (!line)
		handle_error(EMPTY_FILE, NULL);
	while (line)
	{
		if (!is_valid_line(line))
			handle_error(INVALID_LINE, line);
		if (is_texture_line(line))
			parse_textures(game->map, line);
		else if (is_color_line(line))
			parse_color(game->map, line);
		else if (is_map_line(line))
		{
			parse_map(game, fd, line);
			break ;
		}
		line = get_next_line(fd);
	}
	validate(game);
	
	game->texture[NORTH]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		game->map->tex_path[NORTH],
		&game->texture[NORTH]->width,
		&game->texture[NORTH]->height
	);
	game->texture[NORTH]->tex_addr = mlx_get_data_addr(
		game->texture[NORTH]->tex_ptr,
		&game->texture[NORTH]->bpp,
		&game->texture[NORTH]->size_line,
		&game->texture[NORTH]->endian
	);
	
	game->texture[SOUTH]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		game->map->tex_path[SOUTH],
		&game->texture[SOUTH]->width,
		&game->texture[SOUTH]->height
	);
	game->texture[SOUTH]->tex_addr = mlx_get_data_addr(
		game->texture[SOUTH]->tex_ptr,
		&game->texture[SOUTH]->bpp,
		&game->texture[SOUTH]->size_line,
		&game->texture[SOUTH]->endian
	);
	
	game->texture[WEST]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		game->map->tex_path[WEST],
		&game->texture[WEST]->width,
		&game->texture[WEST]->height
	);
	game->texture[WEST]->tex_addr = mlx_get_data_addr(
		game->texture[WEST]->tex_ptr,
		&game->texture[WEST]->bpp,
		&game->texture[WEST]->size_line,
		&game->texture[WEST]->endian
	);
	
	game->texture[EAST]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		game->map->tex_path[EAST],
		&game->texture[EAST]->width,
		&game->texture[EAST]->height
	);
	game->texture[EAST]->tex_addr = mlx_get_data_addr(
		game->texture[EAST]->tex_ptr,
		&game->texture[EAST]->bpp,
		&game->texture[EAST]->size_line,
		&game->texture[EAST]->endian
	);
	
	get_next_line(-42);
	close(fd);
}
