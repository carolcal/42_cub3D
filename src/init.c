/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:47:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/17 10:28:18 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

// t_map *init_map(const char *map_file)
// {
//     t_map *map;
	
//     map = allocate_mem(1, sizeof(t_map));
//     return (map);
// }
// t_player *init_player()


// PARA TESTE
void	manual_init(t_game *game)
{
	// map
	game->map->height = 6;
	game->map->width = 10;
	game->map->grid = allocate_mem(game->map->height, sizeof(int *));

	for (int i = 0; i < game->map->height; i++) {
		game->map->grid[i] = allocate_mem(game->map->width, sizeof(int));
	}
	int row0[10] = {' ',' ',1,1,1,1,1,1,1,1};
	int row1[10] = {1,1,1,0,1,1,0,0,1,1};
	int row2[10] = {1,0,0,0,0,0,0,0,0,1};
	int row3[10] = {1,0,0,0,0,0,0,0,0,1};
	int row4[10] = {1,0,0,0,0,0,0,0,0,1};
	int row5[10] = {1,1,1,1,1,1,1,1,1,1};

	for (int j = 0; j < game->map->width; j++) {
		game->map->grid[0][j] = row0[j];
		game->map->grid[1][j] = row1[j];
		game->map->grid[2][j] = row2[j];
		game->map->grid[3][j] = row3[j];
		game->map->grid[4][j] = row4[j];
		game->map->grid[5][j] = row5[j];
	}
	
	// player
	game->player->pos[0] = 1.5;
	game->player->pos[1] = 4.5;
	game->player->dir[0] = 0;
	game->player->dir[1] = -1;
	game->player->plane[0] = 0.66;
	game->player->plane[1] = 0;
	
	// texture
	game->map->ceiling = 0x87CEEB;
	game->map->floor = 0x8B4513; 
	for (int k = 0; k < 4; k++) {
		game->texture[k] = allocate_mem(1, sizeof(t_texture));
	}
	game->texture[0]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		"assets/textures/castle.xpm",
		&game->texture[0]->width,
		&game->texture[0]->height
	);
	if (!game->texture[0]->tex_ptr)
		handle_error("Failed to load texture.\n");
	game->texture[0]->tex_addr = mlx_get_data_addr(
		game->texture[0]->tex_ptr,
		&game->texture[0]->bpp,
		&game->texture[0]->size_line,
		&game->texture[0]->endian
	);
	game->texture[1]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		"assets/textures/cake.xpm",
		&game->texture[1]->width,
		&game->texture[1]->height
	);
	if (!game->texture[1]->tex_ptr)
		handle_error("Failed to load texture.\n");
	game->texture[1]->tex_addr = mlx_get_data_addr(
		game->texture[1]->tex_ptr,
		&game->texture[1]->bpp,
		&game->texture[1]->size_line,
		&game->texture[1]->endian
	);
	game->texture[2]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		"assets/textures/grass.xpm",
		&game->texture[2]->width,
		&game->texture[2]->height
	);
	if (!game->texture[2]->tex_ptr)
		handle_error("Failed to load texture.\n");
	game->texture[2]->tex_addr = mlx_get_data_addr(
		game->texture[2]->tex_ptr,
		&game->texture[2]->bpp,
		&game->texture[2]->size_line,
		&game->texture[2]->endian
	);
	game->texture[3]->tex_ptr = mlx_xpm_file_to_image(
		game->mlx->mlx_ptr,
		"assets/textures/choco.xpm",
		&game->texture[3]->width,
		&game->texture[3]->height
	);
	if (!game->texture[3]->tex_ptr)
		handle_error("Failed to load texture.\n");
	game->texture[3]->tex_addr = mlx_get_data_addr(
		game->texture[3]->tex_ptr,
		&game->texture[3]->bpp,
		&game->texture[3]->size_line,
		&game->texture[3]->endian
	);
}

t_game	*init(const char *map_file)
{
	t_game	*game;

	(void) map_file;
	game = allocate_mem(1, sizeof(t_game));
	game->map = allocate_mem(1, sizeof(t_map));
	game->player = allocate_mem(1, sizeof(t_player));
	game->mlx = allocate_mem(1, sizeof(t_mlx));
	init_mlx(game); // apagar depois 
	manual_init(game);  // TESTE
	return (game);
}