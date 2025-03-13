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

#define WIDTH 14
#define HEIGHT 9
#define TILE_SIZE 32

void print_map(t_game *game, char **map)
{
	for (int i = 0; i < game->height; i++)
		printf("%s", map[i]);
	printf("\n");
}

char **get_map(char *input, t_game *game)
{
	int		fd;
	int		i;
	char	**ret;
	char	*line;
	
	fd = open(input, O_RDONLY);
	i = 0;
	ret = (char **)ft_calloc(game->height + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while(ret[i] = get_next_line(fd))
		i++;
	close(fd);
	return (ret);
}

mlx_image_t *png_to_image(const char *path, t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*ret;

	texture = mlx_load_png(path);
	ret = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (ret)
			mlx_resize_image(ret, TILE_SIZE, TILE_SIZE);
	return (ret);
}

int check_wall(t_game *game, char *way)
{
	
	if (way == "up")
		if (game->input_map[(game->player->y) - 1][(game->player->x)] != WALL)
			return (1);
	if (way == "down")
		if (game->input_map[game->player->y + 1][(game->player->x)] != WALL)
			return (1);
	if (way == "left")
		if (game->input_map[game->player->y][(game->player->x) - 1] != WALL)
			return (1);
	if (way == "right")
		if (game->input_map[game->player->y][(game->player->x) + 1] != WALL)
			return (1);
	return (0);
}

void move(t_game *game, int way, char axis)
{
	if (game->input_map[game->player->y][game->player->x] != EXIT)
		mlx_image_to_window(game->mlx, game->floor_image, game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
	else
		mlx_image_to_window(game->mlx, game->map[game->player->y][game->player->x].image, game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
	if (axis == 'x')
		game->player->x += way;
	else
		game->player->y += way;
	if (game->input_map[game->player->y][game->player->x] == COLLECT)
		{
			game->collected++;
			game->input_map[game->player->y][game->player->x] = EMPTY;
		}
	if (game->input_map[game->player->y][game->player->x] == EXIT)
		{
			if (game->collected == 0)
				mlx_close_window(game->mlx);
		}
	mlx_image_to_window(game->mlx, game->player->image, game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
}

void movement_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;


	game = param;
	printf("x: %i, y: %i, collected: %i\n", game->player->x, game->player->y, game->collected);
	if(mlx_is_key_down(game->mlx, MLX_KEY_W) && check_wall(game, "up"))
		move(game, -1, 'y');
	else if(mlx_is_key_down(game->mlx, MLX_KEY_A) && check_wall(game, "left"))
		move(game, -1, 'x');
	else if(mlx_is_key_down(game->mlx, MLX_KEY_S) && check_wall(game, "down"))
		move(game, 1, 'y');
	else if(mlx_is_key_down(game->mlx, MLX_KEY_D) && check_wall(game, "right"))
		move(game, 1, 'x');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

t_player *init_player(t_game *game)
{
	t_player *player;
	int y;
	int x;

	player = ft_calloc(sizeof(struct s_player), 1);
	if (!player)
		return (NULL);
	player->texture = mlx_load_png("images/player.png");
	player->image = mlx_texture_to_image(game->mlx, player->texture);
	mlx_delete_texture(player->texture);
	mlx_resize_image(player->image, TILE_SIZE, TILE_SIZE);
	y = 0;
	while(y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->input_map[y][x] == PLAYER)
			{
				player->x = x;
				player->y = y;
				break ;
			}
			x++;
		}
		y++;
	}
	mlx_delete_image(game->mlx, game->map[player->y][player->x].image);
	mlx_image_to_window(game->mlx, player->image, player->x * TILE_SIZE, player->y * TILE_SIZE);
	return (player);
}

t_entity init_entity(t_game *game, int y, int x)
{
	t_entity entity;

	if (game->input_map[y][x] == WALL)
		entity.image = png_to_image("images/wall.png", game);
	else if (game->input_map[y][x] == EMPTY || game->input_map[y][x] == PLAYER)
		entity.image = png_to_image("images/empty_space.png", game);
	else if (game->input_map[y][x] == COLLECT)
	{
		entity.image = png_to_image("images/collectible.png", game);
		game->collected--;
	}
	else if (game->input_map[y][x] == EXIT)
		entity.image = png_to_image("images/exit.png", game);
	else if (game->input_map[y][x] == FLOOD)
		entity.image = png_to_image("images/flood.png", game);
	return (entity);
}

t_game *init_game(int argc, char *argv, t_game *game)
{
	int x;
	int y;

	game->collected = 0;
	game->map = ft_calloc(game->height, sizeof(struct s_entity *));
	if (!game->map)
		return (NULL);
	y = 0;
	game->input_map = get_map(argv, game);
	if (!game->input_map)
		return (NULL);
	while (y < game->height)
	{
		game->map[y] = ft_calloc(game->width, sizeof(struct s_entity));
		if (!game->map)
			return (NULL);
		x = 0;
		while (x < game->width)
		{
			game->map[y][x] = init_entity(game, y, x);
			if (game->map[y][x].image)
				mlx_image_to_window(game->mlx, game->map[y][x].image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	game->floor_image = png_to_image("images/empty_space.png", game);
	game->player = init_player(game);
	if (!game->player)
		return (NULL);
	return (game);
}

int	check_rect(char *input, t_game *game)
{
	int		fd;
	int		i;
	int		nl;
	char	*line;
	
	fd = open(input, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	game->width = (int)ft_strlen(line) - 2;
	free(line);
	while(line = get_next_line(fd))
	{
		nl = 0;
		if (line[ft_strlen(line) - 1] == '\n')
			nl = 1;
		if (game->width != (int)ft_strlen(line) - 2)
		{
			if (!nl)
			{
				if (game->width != (int)ft_strlen(line))
					return (0);
			}
			else
				return (0);	
		}
		i++;
		free(line);
	}
	if (nl)
		return (0);
	game->height = i + 1;
	close(fd);
	return (1);
}

void fill_flood(char **map, int x, int y)
{
	if (map[y + 1][x] != WALL && map[y + 1][x] != FLOOD)
	{
		map[y + 1][x] = FLOOD;
		fill_flood(map, x, y + 1);
	}
	if (map[y - 1][x] != WALL && map[y - 1][x] != FLOOD)
	{
		map[y - 1][x] = FLOOD;
		fill_flood(map, x, y - 1);
	}
	if (map[y][x + 1] != WALL && map[y][x + 1] != FLOOD)
	{
		map[y][x + 1] = FLOOD;
		fill_flood(map, x + 1, y);
	}
	if (map[y][x - 1] != WALL && map[y][x - 1] != FLOOD)
	{
		map[y][x - 1] = FLOOD;
		fill_flood(map, x - 1, y);
	}
}

int check_flood(char **map, int width, int height)
{
	int x;
	int y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == EMPTY)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	flood_test(t_game *game)
{
	char **map;
	int i;

	i = 0;
	map = malloc(sizeof(char *) * game->height);
	while(i < game->height)
	{
		map[i] = ft_strdup(game->input_map[i]);
		i++;
	}
	fill_flood(map, game->player->x, game->player->y);
	print_map(game, game->input_map);
	print_map(game, map);
	return (check_flood(map, game->width, game->height));
}

int main(int argc, char **argv)
{
	t_game *game;
	mlx_image_t* image;

	if (argc < 2 || argc > 2)
		return (printf("no inputs\n"), -1);
	game = malloc(sizeof(struct s_game));
	if (!game)
	{
		printf("malloc game failed\n");
		return (EXIT_FAILURE);
	}
	if (!check_rect(argv[1], game))
	{
		printf("not rectangle\n");
		free(game);
		return (EXIT_FAILURE);
	}
	printf("width: %i height: %i\n", game->width, game->height);
	if(!(game->mlx = mlx_init(game->width * TILE_SIZE, game->height * TILE_SIZE, "so_long", true)))
	{
		printf("mlx_init fail\n");
		free(game);
		return (EXIT_FAILURE);
	}
	game = init_game(argc, argv[1], game);
	if (!game)
	{
		printf("init_game fail\n");
		return (EXIT_FAILURE);
	}
	if (!flood_test(game))
	{
		printf("flood_test failed\n");
		free(game);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(game->mlx, movement_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
