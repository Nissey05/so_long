/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:17:58 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/14 21:17:58 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/so_long.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

t_game *init(t_game *game, char **argv, int argc)
{
	game = malloc(sizeof(struct s_game));
	if (!game)
		return (ft_printf("malloc game failed\n"), NULL);
	if (!check_rect(argv[1], game))
	{
		ft_printf("not rectangle\n");
		free(game);
		return (NULL);
	}
	ft_printf("width: %i height: %i\n", game->width, game->height);
	game->mlx = mlx_init(game->width * TILE_SIZE, game->height * TILE_SIZE, "so_long", true);
	if (!(game->mlx))
	{
		ft_printf("mlx_init fail\n");
		free(game);
		return (NULL);
	}
	game = init_game(argc, argv[1], game);
	if (!game)
		return (ft_printf("init_game fail\n"), NULL);
	return (game);
}

t_images *init_images(t_game *game)
{
	t_images *img;

	img = ft_calloc(1, sizeof(struct s_images *));
	if (!img)
		return (NULL);
	img->empty = png_to_image("images/empty_space.png", game);
	img->wall = png_to_image("images/wall.png", game);
	img->collect = png_to_image("images/Collectible.png", game);
	img->exit = png_to_image("images/Exit.png", game);
	img->flood = png_to_image("images/Flood.png", game);
	return (img);
}

t_game	*init_game(int argc, char *argv, t_game *game)
{
	int	x;
	int	y;

	game->collected = 0;
	game->move_count = 0;
	game->map = ft_calloc(game->height, sizeof(struct s_entity *));
	if (!game->map)
		return (NULL);
	y = 0;
	game->input_map = get_map(argv, game);
	if (!game->input_map)
		return (NULL);
	game->images = init_images(game);
	if (!game->images)
		return (NULL);
	while (y < game->height)
	{
		game->map[y] = ft_calloc(game->width, sizeof(struct s_entity));
		if (!game->map)
			return (NULL);
		x = 0;
		printf("%s", game->input_map[y]);
		while (x < game->width)
		{
			// ft_printf("%i\n", x);
			game->map[y][x] = init_entity(game, y, x);
			if (game->map[y][x].image)
				mlx_image_to_window(game->mlx, game->map[y][x].image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	printf("\n");
	game->floor_image = png_to_image("images/empty_space.png", game);
	game->player = init_player(game);
	if (!game->player)
		return (NULL);
	return (game);
}

t_entity	init_entity(t_game *game, int y, int x)
{
	t_entity	entity;

	if (game->input_map[y][x] == WALL)
		entity.image = game->images->wall;
	else if (game->input_map[y][x] == EMPTY)
		entity.image = game->images->empty;
	else if (game->input_map[y][x] == COLLECT)
	{
		entity.image = game->images->collect;
		game->collected--;
	}
	else if (game->input_map[y][x] == EXIT)
		entity.image = game->images->exit;
	else if (game->input_map[y][x] == FLOOD)
		entity.image = game->images->flood;
	else
		entity.image = NULL;
	return (entity);
}

t_player	*init_player(t_game *game)
{
	t_player	*player;
	int			y;
	int			x;

	player = ft_calloc(sizeof(struct s_player), 1);
	if (!player)
		return (NULL);
	player->image = png_to_image("images/player.png", game);
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->input_map[y][x] == PLAYER)
			{
				player->x = x;
				player->y = y;
				break ;
			}
		}
	}
	mlx_image_to_window(game->mlx, player->image, player->x * TILE_SIZE, player->y * TILE_SIZE);
	return (player);
}
