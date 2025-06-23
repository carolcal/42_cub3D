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

# include "cub3D.h"

void    handle_error(char *error)
{
	ft_printf_fd(2, error);
	clear_mem();
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	game = init(argv[1]);
	// validate_map_file(game, argv[1]);
	// init_mlx(game);
	render_img(game);
	start_game(argv[1]);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keys, game);
	mlx_hook(game->mlx->win_ptr, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx->mlx_ptr, render_img, game);
	mlx_loop(game->mlx->mlx_ptr);
	clear_mem();
	return (EXIT_SUCCESS);
}
