/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/27 15:09:43 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		handle_error("Error: Failed to initialize MLX.\n", NULL);
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx->win_ptr)
		handle_error("Error: Failed to create MLX window.\n", NULL);
	game->mlx->img_ptr = mlx_new_image(game->mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx->img_ptr)
		handle_error("Error: Failed to create image.\n", NULL);
	game->mlx->img_addr = mlx_get_data_addr(game->mlx->img_ptr,
			&game->mlx->bpp, &game->mlx->size_line, &game->mlx->endian);
	if (!game->mlx->img_addr)
		handle_error("Error: Failed to get image address.\n", NULL);
	return ;
}

void	parse_mlx(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i]->tex_ptr = mlx_xpm_file_to_image(
				game->mlx->mlx_ptr,
				game->map->tex_path[i],
				&game->texture[i]->width,
				&game->texture[i]->height
				);
		game->texture[i]->tex_addr = mlx_get_data_addr(
				game->texture[i]->tex_ptr,
				&game->texture[i]->bpp,
				&game->texture[i]->size_line,
				&game->texture[i]->endian
				);
		i++;
	}
}

static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i] && game->texture[i]->tex_ptr)
		{
			mlx_destroy_image(game->mlx->mlx_ptr, game->texture[i]->tex_ptr);
			game->texture[i]->tex_ptr = NULL;
		}
		i++;
	}
}

int	close_window(t_game *game)
{
	free_textures(game);
	if (game->mlx->img_ptr)
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->img_ptr);
	if (game->mlx->win_ptr)
		mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	if (game->mlx->mlx_ptr)
	{
		mlx_destroy_display(game->mlx->mlx_ptr);
		free(game->mlx->mlx_ptr);
	}
	clear_mem();
	exit(EXIT_SUCCESS);
	return (0);
}
