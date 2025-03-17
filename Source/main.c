/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:10:51 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/12 23:10:51 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../Include/so_long.h"

void print_map(t_game *game, char **map)
{
	for (int i = 0; i < game->height; i++)
		printf("%s", map[i]);
	printf("\n");
}


int	main(int argc, char **argv)
{
	t_game			*game;
	mlx_image_t		*image;

	if (argc < 2 || argc > 2)
		return (printf("no inputs\n"), -1);
	if (!check_extension(argv[1]))
		return (printf("incorrect extension\n"), -1);
	game = init(game, argv, argc);
	if (!game)
		return (EXIT_FAILURE);
	if (!check_map(game))
	{
		printf("check_map failed\n");
		free_game(game);
		return (EXIT_FAILURE);
	}
	if (flood_test(game))
	{
		printf("flood_test failed\n");
		free_game(game);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(game->mlx, movement_hook, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
