/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:11:41 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/26 11:33:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	is_valid_line(char *line)
{
	if (!line)
		return (0);
	return (is_texture_line(line) || is_color_line(line)
		|| is_map_line(line) || is_empty_line(line));
}

bool	is_texture_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	return ((ft_strncmp(line + i, "NO", 2) == 0
			|| ft_strncmp(line + i, "SO", 2) == 0
			|| ft_strncmp(line + i, "WE", 2) == 0
			|| ft_strncmp(line + i, "EA", 2) == 0)
		&& ft_isspace(line[i + 2]));
}

bool	is_color_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	return ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]));
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	return (line[i] == '1' || line[i] == '0');
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	return (line[i] == '\0' || line[i] == '\n');
}
