/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_property.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:59:43 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/17 18:46:34 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int validate_color_line(char *line)
{
    int i;
    
    i = 1;
    while (line[i] == ' ')
        i++;
    
}

uint32_t get_color(char *line)
{
    //get color
}

void    parse_color(t_map *map, char *line)
{
    uint32_t color;
    
    if (!validate_color_line(line))
        handle_error(INVALID_COLOR);
    color = get_color(line);
    if (line[0] == 'F')
        map->floor = color;
    else
        map->ceiling = color;
}

int     validate_texture_line(char *line)
{
    //validate texture line
}

char    *get_texture(char *line)
{
    //get texture
}

void    parse_texture(t_map *map, char *line)
{
    char    *texture;
    
    if (!validate_texture_line(line))
        handle_error(INVALID_TEXTURE);
    texture = get_texture(line);
    if (ft_strncmp(line, "NO", 2))
        map->texture->noth = texture;
    else if (ft_strncmp(line, "SO", 2))
        map->texture->south = texture;
    else if (ft_strncmp(line, "WE", 2))
        map->texture->west = texture;
    else
        map->texture->east = texture;
}

void    parse_property(t_map *map, char *line)
{
    if (line[0] == 'F' || line[1] == 'C')
        parse_color(map, line);
    else if (ft_strncmp(line, "NO", 2) || ft_strncmp(line, "SO", 2) ||
            ft_strncmp(line, "WE", 2) || ft_strncmp(line, "EA", 2))
        parse_texture(map, line);
    else
        handle_error(INVALID_FILE);
}
