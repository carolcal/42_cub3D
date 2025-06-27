/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:46:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_mlx(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i]->tex_ptr = mlx_xpm_file_to_image(
				game->mlx->mlx_ptr,
				game->map->tex_path[i],
				&game->texture[i]->width,
				&game->texture[i]->height
				);
		game->texture[i]->tex_addr = mlx_get_data_addr(
				game->texture[i]->tex_ptr,
				&game->texture[i]->bpp,
				&game->texture[i]->size_line,
				&game->texture[i]->endian
				);
	}
}

static int	exec_parse(t_game *game, char *line, int fd)
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
		return (1);
	}
	return (0);
}

void	parse_file(t_game *game, const char *map_file)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE, (char *)map_file);
	line = get_next_line(fd);
	if (!line)
		handle_error(EMPTY_FILE, NULL);
	while (line)
	{
		if (exec_parse(game, line, fd))
			break ;
		line = get_next_line(fd);
	}
	validate(game);
	parse_mlx(game);
	get_next_line(-42);
	close(fd);
}
