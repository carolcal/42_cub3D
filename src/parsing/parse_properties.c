/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:59:43 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:29:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_texture(char **texture_slot, char *line)
{
	char	*texture_path;

	if (*texture_slot != NULL)
		handle_error(DUPLICATE_TEXTURE, *texture_slot);
	texture_path = ft_strtrim(line + 2, " \t\n\f\r\v");
	*texture_slot = texture_path;
}

void	parse_textures(t_map *map, char *line)
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
	int		k;
	char	*color;

	k = 0;
	while (ft_isspace(rgb[*i]))
		(*i)++;
	if (!rgb[*i])
		handle_error(INVALID_COLOR, rgb);
	while (rgb[*i + k] && rgb[*i + k] != ',' && rgb[*i + k] != '\n'
		&& !ft_isspace(rgb[*i + k]))
	{
		if (!ft_isdigit(rgb[*i + k]))
			handle_error(INVALID_COLOR, rgb);
		k++;
	}
	if (k < 1 || k > 4)
		handle_error(INVALID_COLOR, rgb);
	color = allocate_mem((k + 1), sizeof(char));
	if (!color)
		handle_error(MEMORY_ERROR, NULL);
	ft_strlcpy(color, rgb + *i, k + 1);
	k++;
	*i += k;
	return (color);
}

static uint32_t	convert_rgb(char *line)
{
	int		i;
	int		j;
	int		rgb[3];

	i = 1;
	j = 0;
	while (j < 3)
	{
		rgb[j] = ft_atoi(get_color(line, &i));
		if (rgb[j] < 0 || rgb[j] > 255)
			handle_error(INVALID_COLOR, line);
		j++;
	}
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isspace(line[i]))
			handle_error(INVALID_COLOR, line);
		i++;
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	parse_color(t_map *map, char *line)
{
	uint32_t	color;

	while (ft_isspace(*line))
		line++;
	color = convert_rgb(line);
	if (line[0] == 'F')
		map->floor = color;
	else
		map->ceiling = color;
}
