/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:19:56 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/14 21:19:56 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/so_long.h"
#include <unistd.h>
#include <fcntl.h>

char	**get_map(char *input, t_game *game)
{
	int		fd;
	int		i;
	char	**ret;
	char	*line;

	fd = open(input, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("invalid file\n");
		return (NULL);
	}
	i = 0;
	ret = (char **)ft_calloc(game->height + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (ret[i] = get_next_line(fd))
		i++;
	close(fd);
	return (ret);
}

mlx_image_t	*png_to_image(const char *path, t_game *game)
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

int	count_map(char **map, t_game *game, char item)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (map[y][x] == item)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	check_map(t_game *game)
{
	if (count_map(game->input_map, game, PLAYER) != 1)
		return (0);
	if (count_map(game->input_map, game, COLLECT) < 1)
		return (0);
	if (count_map(game->input_map, game, EXIT) != 1)
		return (0);
	if (!check_border(game->input_map, game->width, game->height))
		return (0);
	return (check_all(game));
}
