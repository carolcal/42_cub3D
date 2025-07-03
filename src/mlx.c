/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/27 16:00:36 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		handle_error(MLX_INIT, NULL);
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx->win_ptr)
		handle_error(MLX_WIN, NULL);
	game->mlx->img_ptr = mlx_new_image(game->mlx->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx->img_ptr)
		handle_error(MLX_IMG, NULL);
	game->mlx->img_addr = mlx_get_data_addr(game->mlx->img_ptr,
			&game->mlx->bpp, &game->mlx->size_line, &game->mlx->endian);
	if (!game->mlx->img_addr)
		handle_error(MLX_ADDR, NULL);
	return ;
}

static void	init_texture(t_texture *texture, char *tex_path, t_mlx *mlx)
{
	texture->tex_ptr = mlx_xpm_file_to_image(
			mlx->mlx_ptr,
			tex_path,
			&texture->width,
			&texture->height
			);
	if (!texture->tex_ptr)
		handle_error(MLX_TEX_INIT, NULL);
	texture->tex_addr = mlx_get_data_addr(
			texture->tex_ptr,
			&texture->bpp,
			&texture->size_line,
			&texture->endian
			);
	if (!texture->tex_addr)
		handle_error(MLX_TEX_ADDR, NULL);
}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		init_texture(game->texture[i], game->map->tex_path[i], game->mlx);
		//BONUS
		init_texture(game->enemy_texture[i], game->enemy_tex_path[i], game->mlx);
		init_texture(game->goal_texture[i], game->goal_tex_path[i], game->mlx);
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
		if (game->enemy_texture[i] && game->enemy_texture[i]->tex_ptr)
		{
			mlx_destroy_image(game->mlx->mlx_ptr, game->enemy_texture[i]->tex_ptr);
			game->enemy_texture[i]->tex_ptr = NULL;
		}
		if (game->goal_texture[i] && game->goal_texture[i]->tex_ptr)
		{
			mlx_destroy_image(game->mlx->mlx_ptr, game->goal_texture[i]->tex_ptr);
			game->goal_texture[i]->tex_ptr = NULL;
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
