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

t_game *init(const char *map_file)
{
    t_game *game;

    
    printf("Initializing with map: %s\n", map_file);
}

void    validate_map(const char *map_file)
{
    printf("Validating map: %s\n", map_file);
}

void    init_game(const char *map_file)
{
    printf("Initializing game with map: %s\n", map_file);
}

int    main(int argc, char **argv)
{
    t_game *game;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    game = init(argv[1]);
    validate_map(argv[1]);
    init_game(argv[1]);

    return (EXIT_SUCCESS);
}