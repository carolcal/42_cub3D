/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/25 16:54:25 by cayamash         ###   ########.fr       */
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
		free(line);
		line = get_next_line(fd);
	}
	validate(game);
	get_next_line(-42);
	close(fd);
}
