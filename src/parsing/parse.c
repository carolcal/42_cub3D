/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/27 15:59:32 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	get_next_line(-42);
	validate(game);
	init_mlx(game);
	init_textures(game);
	close(fd);
}
