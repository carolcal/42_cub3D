/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/17 18:42:06 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int    validate_map_file(t_game *game, const char *map_file)
{
	int     fd;
	char    *line;

	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (is_alpha(line[0]))
			parce_property(game->map, line);
		else if (ft_strchr(line, '0') || ft_strchr(line, '1'))
			parse_map(game, fd, line);
		else if (!empty_line(line))
			handle_error(INVALID_MAP);
		else
			line = get_next_line(fd);
	}
	close(fd);
}
