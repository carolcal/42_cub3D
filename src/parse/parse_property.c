/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_property.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:59:43 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/23 15:39:41 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

char	*validate_texture(char *line)
{
	int		i;
	int		fd;
	int		path_len;
	char	*path;

	i = 2;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	path_len = line_len(line + i);
	path = ft_substr(line + i, 0, path_len -1);
	if (!path)
		handle_error(INVALID_TEXTURE);
	if (path_len < 5)
		handle_error(INVALID_TEXTURE);
	if (ft_strncmp(path + path_len - 5, ".png", 4) != 0 &&
			ft_strncmp(path + path_len - 5, ".jpg", 4) != 0 &&
			ft_strncmp(path + path_len - 6, ".jpeg", 5) != 0)
		handle_error(INVALID_TEXTURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_TEXTURE);
	close(fd);
	return (path);
}

void    parse_texture(t_map *map, char *line)
{
    char    *texture;
    printf("parse texture\n");
    texture = validate_texture(line);
    if (ft_strncmp(line, "NO", 2) == 0)
        map->texture[NORTH] = texture;
    else if (ft_strncmp(line, "SO", 2) == 0)
        map->texture[SOUTH] = texture;
    else if (ft_strncmp(line, "WE", 2) == 0)
        map->texture[WEST] = texture;
    else
        map->texture[EAST] = texture;
}

void    parse_property(t_map *map, char *line)
{
    if (line[0] == 'F' || line[0] == 'C')
        parse_color(map, line);
    else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
            ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
        parse_texture(map, line);
    else
        handle_error(INVALID_FILE);
}
