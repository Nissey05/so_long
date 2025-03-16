/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:01:01 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/16 22:01:01 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../Include/so_long.h"
#include <stdlib.h>

void	free_game(t_game *game)
{
	int	i;

	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->input_map)
	{
		i = -1;
		while (++i < game->height && game->input_map[i])
			free(game->input_map[i]);
		free(game->input_map);
	}
	if (game->map)
	{
		i = -1;
		while (++i < game->height && game->map[i])
			free(game->map[i]);
		free(game->map);
	}
	if (game->player)
		free(game->player);
	free(game);
}
