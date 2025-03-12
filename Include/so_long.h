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
	char			**input_map;
	int				width;
	int				height;
	int				collected;
	mlx_image_t		*floor_image;
	t_player		*player;
}					t_game;

#endif