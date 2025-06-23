/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:48:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/23 16:25:36 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int is_space_or_one(char c)
{
	if (ft_isspace(c) || c == '1')
		return (1);
	return (0);
}

int	line_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}

void    parse_map_file(t_game *game, const char *map_file)
{
	int     fd;
	char    *line;

	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_isalpha(line[0]))
		{
			parse_property(game->map, line);
			line = get_next_line(fd);
		}
		else if (ft_strchr(line, '0') || ft_strchr(line, '1'))
			parse_map(game, fd, line);
		else if (!empty_line(line))
			handle_error(INVALID_FILE);
		else
			line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
