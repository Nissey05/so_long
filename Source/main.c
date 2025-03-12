// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../Include/so_long.h"

#define WIDTH 10
#define HEIGHT 5
#define TILE_SIZE 128

static mlx_image_t* imagery;

//// -----------------------------------------------------------------------------

//int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
//{
//    return (r << 24 | g << 16 | b << 8 | a);
//}

//void ft_randomize(void* param)
//{
//	(void)param;
//	for (uint32_t i = 0; i < image->width; ++i)
//	{
//		for (uint32_t y = 0; y < image->height; ++y)
//		{
//			uint32_t color = ft_pixel(
//				rand() % 0xFF, // R
//				rand() % 0xFF, // G
//				rand() % 0xFF, // B
//				rand() % 0xFF  // A
//			);
//			mlx_put_pixel(image, i, y, color);
//		}
//	}
//}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		imagery->instances[0].y -= 2.5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		imagery->instances[0].y += 2.5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		imagery->instances[0].x -= 2.5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		imagery->instances[0].x += 2.5;
}

//// -----------------------------------------------------------------------------

//int32_t main(void)
//{
//	mlx_t* mlx;

//	// Gotta error check this stuff
//	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
//	{
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
//	if (!(image = mlx_new_image(mlx, 128, 128)))
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
//	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
//	{
//		mlx_close_window(mlx);
//		puts(mlx_strerror(mlx_errno));
//		return(EXIT_FAILURE);
//	}
	
//	mlx_loop_hook(mlx, ft_randomize, mlx);
//	mlx_loop_hook(mlx, ft_hook, mlx);

//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (EXIT_SUCCESS);
//}

void print_map(t_game *game)
{
	for (int i = 0; i < 5; i++)
		printf("%s", game->input_map[i]);
	printf("\n");
}

char **get_map(char *input)
{
	int fd;
	int i;
	char **ret;
	
	fd = open(input, O_RDONLY);
	i = 0;
	ret = (char **)ft_calloc(sizeof(char *), HEIGHT);
	while(ret[i] = get_next_line(fd))
		i++;
	return (ret);
}

void movement_hook(void *param)
{
	t_game *game;

	game = param;
	if(mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->y += TILE_SIZE;
	if(mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->x -= TILE_SIZE;
	if(mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->y -= TILE_SIZE;
	if(mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->x += TILE_SIZE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

t_player *init_player(t_game *game)
{
	t_player *player;
	int y;
	int x;

	player = (t_player *)ft_calloc(1, sizeof(t_player));
	player->texture = mlx_load_png("images/player.png");
	player->image = mlx_texture_to_image(game->mlx, player->texture);
	mlx_delete_texture(player->texture);
	mlx_resize_image(player->image, TILE_SIZE, TILE_SIZE);
	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
		entity.texture = mlx_load_png("images/wall.png");
	else if (game->input_map[y][x] == EMPTY || game->input_map[y][x] == PLAYER)
		entity.texture = mlx_load_png("images/empty_space.png");
	else if (game->input_map[y][x] == COLLECT)
		entity.texture = mlx_load_png("images/collectible.png");
	else if (game->input_map[y][x] == EXIT)
		entity.texture = mlx_load_png("images/exit.png");
	else if (game->input_map[y][x] == FLOOD)
		entity.texture = mlx_load_png("images/flood.png");
	if(entity.texture)
	{
		entity.image = mlx_texture_to_image(game->mlx, entity.texture);
		mlx_delete_texture(entity.texture);
		if (entity.image)
			mlx_resize_image(entity.image, TILE_SIZE, TILE_SIZE);
	}
	return (entity);
}

t_game *init_game(int argc, char *argv, t_game *game)
{
	int x;
	int y;

	game->map = (t_entity **)ft_calloc(sizeof(t_entity *), HEIGHT);
		if (!game->map)
			return (NULL);
	y = 0;
	game->input_map = get_map(argv);
	while (y < HEIGHT)
	{
		game->map[y] = (t_entity *)ft_calloc(sizeof(t_entity), WIDTH);
		if (!game->map)
			return (NULL);
		x = 0;
		while (x < WIDTH)
		{
			game->map[y][x] = init_entity(game, y, x);
			if (game->map[y][x].image)
				mlx_image_to_window(game->mlx, game->map[y][x].image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	game->player = init_player(game);
	return (game);
}

void draw_to_window(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_image_to_window(game->mlx, game->map[y][x].image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int main(int argc, char **argv)
{
	t_game *game;
	mlx_image_t* image;

	if (argc < 2 || argc > 2)
		return (printf("no inputs\n"), -1);
	game = (t_game *)malloc(sizeof(t_game));
	if(!(game->mlx = mlx_init(WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE, "so_long", true)))
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
	//draw_to_window(game);
	//if(!image)
	//	printf("ERROR 2\n");
	mlx_loop_hook(game->mlx, movement_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

//int main(void)
//{
//	mlx_t *mlx;
//	mlx_image_t *image;
//	mlx_texture_t *texture;
//	mlx = mlx_init(WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE, "so_long", true);
//	texture = mlx_load_png("images/wall.png");
//	image = mlx_texture_to_image(mlx, texture);
//	//mlx_delete_texture(texture);
//	mlx_image_to_window(mlx, image, 0, 0);
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (EXIT_SUCCESS);
//}