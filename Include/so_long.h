/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhendrik <nhendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:33:16 by nhendrik          #+#    #+#             */
/*   Updated: 2025/03/09 19:33:16 by nhendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONGH
# define SO_LONGH

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define TILE_SIZE 64
# define EMPTY '0'
# define WALL '1'
# define COLLECT 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define FLOOD 'F'


typedef struct		s_entity
{
	mlx_image_t		*image;
}					t_entity;

typedef struct		s_images
{
	mlx_image_t		*empty;
	mlx_image_t		*wall;
	mlx_image_t		*collect;
	mlx_image_t		*exit;
	mlx_image_t		*flood;
}					t_images;

typedef struct		s_player
{
	int				x;
	int				y;
	mlx_image_t		*image;
	mlx_texture_t 	*texture;
}					t_player;

typedef struct		s_game
{
	mlx_t			*mlx;
	t_entity		**map;
	t_images		*images;
	char			**input_map;
	int				width;
	int				height;
	int				collected;
	int				move_count;
	mlx_image_t		*floor_image;
	t_player		*player;
}					t_game;

int			flood_test(t_game *game);

void		movement_hook(mlx_key_data_t keydata, void *param);
void		move(t_game *game, int way, char axis);

int			check_all(t_game *game);
int			check_border(char **map, int width, int height);
int			check_rect(char *input, t_game *game);
int			check_wall(t_game *game, char *way);
int			check_map(t_game *game);
int			check_extension(char *str);
int			count_map(char **map, t_game *game, char item);
char		**get_map(char *input, t_game *game);
mlx_image_t	*png_to_image(const char *path, t_game *game);

t_game		*init(t_game *game, char **argv, int argc);
t_game		*init_game(int argc, char *argv, t_game *game);
t_entity	init_entity(t_game *game, int y, int x);
t_player	*init_player(t_game *game);
t_images	*init_images(t_game *game);

void		print_map(t_game *game, char **map);
void		free_game(t_game *game);

#endif