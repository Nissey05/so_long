/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:20:24 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/14 21:20:24 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/so_long.h"
#include <stdlib.h>

void	fill_flood(char **map, int x, int y)
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

int	flood_test(t_game *game)
{
	char	**map;
	int		i;
	int		count;

	i = 0;
	map = malloc(sizeof(char *) * game->height);
	while (i < game->height)
	{
		map[i] = ft_strdup(game->input_map[i]);
		i++;
	}
	fill_flood(map, game->player->x, game->player->y);
	count = count_map(map, game, PLAYER);
	count += count_map(map, game, COLLECT);
	count += count_map(map, game, EXIT);
	return (count);
}
