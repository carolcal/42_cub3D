/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:59:43 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/25 18:10:54 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void	set_texture(char **texture_slot, char *line)
{
	char	*texture_path;

	if (*texture_slot != NULL)
		handle_error(DUPLICATE_TEXTURE, *texture_slot);
	texture_path = ft_strtrim(line + 2, " \t\n\f\r\v");
	*texture_slot = texture_path;
}

void    parse_textures(t_map *map, char *line)
{
	while (ft_isspace(*line))
		line++;
    if (ft_strncmp(line, "NO", 2) == 0)
		set_texture(&map->tex_path[NORTH], line);
    else if (ft_strncmp(line, "SO", 2) == 0)
		set_texture(&map->tex_path[SOUTH], line);
    else if (ft_strncmp(line, "WE", 2) == 0)
		set_texture(&map->tex_path[WEST], line);
    else
		set_texture(&map->tex_path[EAST], line);
}

static char	*get_color(char *rgb, int *i)
{
	int		j;
	char	*color;
	
	j = 0;
	while (ft_isspace(rgb[*i]))
		(*i)++;
	if (!rgb[*i])
		handle_error(INVALID_COLOR, rgb);
	while (rgb[*i + j] && rgb[*i + j] != ',' && rgb[*i + j] != '\n' && !ft_isspace(rgb[*i + j]))
	{
		if (!ft_isdigit(rgb[*i + j]))
			handle_error(INVALID_COLOR, rgb);
		j++;
	}
	if (j < 1 || j > 4)
		handle_error(INVALID_COLOR, rgb);
	color = allocate_mem(j, sizeof(char));
	if (!color)
		handle_error(MEMORY_ERROR, NULL);
	ft_strlcpy(color, rgb + *i, j + 1);
	j++;
	*i += j;
	return (color);
}

static uint32_t convert_rgb(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	r = ft_atoi(get_color(line, &i));
	g = ft_atoi(get_color(line, &i));
	b = ft_atoi(get_color(line, &i));
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isspace(line[i]))
			handle_error(INVALID_COLOR, line);
		i++;
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		handle_error(INVALID_COLOR, line);
	return ((r << 16) | (g << 8) | b);
}

void    parse_color(t_map *map, char *line)
{
	uint32_t color;

	while (ft_isspace(*line))
		line++;
    color = convert_rgb(line);
    if (line[0] == 'F')
        map->floor = color;
    else
        map->ceiling = color;
}