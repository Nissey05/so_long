/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:19:58 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/14 21:19:58 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/so_long.h"

void	move(t_game *game, int way, char axis)
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
	game->move_count++;
	ft_printf("Moves: %i\n", game->move_count);
	mlx_image_to_window(game->mlx, game->player->image, game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
}

void	movement_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && check_wall(game, "up"))
		move(game, -1, 'y');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) && check_wall(game, "left"))
		move(game, -1, 'x');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) && check_wall(game, "down"))
		move(game, 1, 'y');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) && check_wall(game, "right"))
		move(game, 1, 'x');	
	else if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
