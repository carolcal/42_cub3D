/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:12:41 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/24 10:38:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}

char	*get_color(char *rgb, int *i)
{
	int		j;
	char	*color;
	
	j = 0;
	while (rgb[*i] == ' ' || (rgb[*i] >= 9 && rgb[*i] <= 13))
		(*i)++;
	while (rgb[*i + j] && rgb[*i + j] != ',' && rgb[*i + j] != ' ' &&
		!(rgb[*i + j] >= 9 && rgb[*i + j] <= 13))
		j++;
	if (j < 1 || j > 4)
		handle_error(INVALID_COLOR);
	color = allocate_mem(j, sizeof(char));
	if (!color)
		handle_error(MEMORY_ERROR);
	ft_strlcpy(color, rgb + *i, j + 1);
	j++;
	*i += j;
	return (color);
}

uint32_t validate_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	r = ft_atoi(get_color(line, &i));
	g = ft_atoi(get_color(line, &i));
	b = ft_atoi(get_color(line, &i));
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		handle_error(INVALID_COLOR);
	return (rgb_to_uint32(r, g, b));
}

void    parse_color(t_map *map, char *line)
{
    uint32_t color;
    color = validate_color(line);
    if (line[0] == 'F')
        map->floor = color;
    else
        map->ceiling = color;
}