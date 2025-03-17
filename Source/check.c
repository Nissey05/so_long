/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:22:48 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/14 21:22:48 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/so_long.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	check_wall(t_game *game, char *way)
{
	if (ft_strncmp(way, "up", 2) == 0)
		if (game->input_map[(game->player->y) - 1][(game->player->x)] != WALL)
			return (1);
	if (ft_strncmp(way, "down", 4) == 0)
		if (game->input_map[game->player->y + 1][(game->player->x)] != WALL)
			return (1);
	if (ft_strncmp(way, "left", 4) == 0)
		if (game->input_map[game->player->y][(game->player->x) - 1] != WALL)
			return (1);
	if (ft_strncmp(way, "right", 5) == 0)
		if (game->input_map[game->player->y][(game->player->x) + 1] != WALL)
			return (1);
	return (0);
}

int	check_rect(char *input, t_game *game)
{
	int		fd;
	int		i;
	int		nl;
	char	*line;

	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	game->width = (int)ft_strlen(line) - 2;
	free(line);
	line = get_next_line(fd);
	while (line)
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
		line = get_next_line(fd);
	}
	if (nl)
		return (0);
	game->height = i + 1;
	close(fd);
	return (1);
}

int	check_all(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->input_map[y][x] != EMPTY && game->input_map[y][x] != WALL && game->input_map[y][x] != COLLECT && game->input_map[y][x] != PLAYER && game->input_map[y][x] != EXIT)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_border(char **map, int width, int height)
{
	int	i;

	i = -1;
	while (++i < width)
		if (map[0][i] != WALL && map[0][i] != '\n' && map[0][i] != '\0')
			return (0);
	i = 0;
	while (map[++i])
	{
		if (map[i][0] != WALL || map[i][width - 1] != WALL)
			return (0);
	}
	i = -1;
	while (map[height - 1][++i])
		if (map[height - 1][i] != WALL)
			return (0);
	return (1);
}

int	check_extension(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 4 && (ft_strncmp(&str[len - 4], ".ber", 4) == 0))
		return (1);
	return (0);
}
