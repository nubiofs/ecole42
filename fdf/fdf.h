/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:51:47 by mprevot           #+#    #+#             */
/*   Updated: 2017/04/24 12:51:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>
#include "libft/libft.h"

typedef struct			s_pixel
{
	size_t				x;
	size_t				y;
	size_t				c;
}						t_pixel;

typedef struct			s_position
{
	size_t				x;
	size_t				y;
	size_t				z;
	size_t				c;
}						t_position;


t_pixel	ft_mlx_getpixel(size_t x, size_t y);
t_position ft_mlx_getposition(size_t x, size_t y, size_t z);
void	ft_mlx_draw(void *mlx, void *win, t_pixel start, t_pixel stop);
void	ft_mlx_3draw(void *mlx, void *win, t_position start, t_position stop);
int		ft_abs(int val);
