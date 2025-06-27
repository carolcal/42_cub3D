/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:23 by marvin            #+#    #+#             */
/*   Updated: 2025/06/12 16:30:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_error(char *error, char *str)
{
	ft_printf_fd(2, error);
	if (str)
	{
		ft_printf_fd(2, ": ");
		ft_printf_fd(2, str);
	}
	ft_printf_fd(2, "\n");
	clear_mem();
	exit(EXIT_FAILURE);
}

void	validate_file(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		handle_error(INVALID_FORMAT, file_name);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	validate_file(argv[1]);
	game = init(argv[1]);
	parse_file(game, argv[1]);
	render_img(game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keys, game);
	mlx_hook(game->mlx->win_ptr, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx->mlx_ptr, render_img, game);
	mlx_loop(game->mlx->mlx_ptr);
	clear_mem();
	return (EXIT_SUCCESS);
}
