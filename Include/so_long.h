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
# include "../Include/so_long.h"

typedef struct		s_entity
{
	mlx_image_t *image;
}					t_entity;

typedef struct		s_game
{
	mlx_t			*mlx;
	t_entity		**entities;
	int				width;
	int				height;
}					t_game;

typedef struct		s_player
{
	int			x;
	int			y;
	mlx_image_t	*image;

}					t_player;

#endif