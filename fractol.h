/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:28:01 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/29 19:19:40 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include "libft/libft.h"
#include <mlx.h>
#include <stdio.h> // test

typedef struct	s_coord
{
				int x;
				int y;
}				t_coord;

typedef	struct	s_image
{
	void		*adr;
	char		*img;
	int			endian;
	int			bpp;
	int			size_l;
}				t_image;

typedef struct	s_env
{
	void		*img;
	void		*win;
	void		*mlx;
	t_image		image;
}				t_env;

int		get_color(int z_i);

void	do_f_julia(t_env *env);
void	do_f_mandelbrot(t_env *env);
void	do_fractal(t_env *env, int id);

#endif
