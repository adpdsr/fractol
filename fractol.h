/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:28:01 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/17 20:49:42 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <mlx.h>
#include "libft/libft.h"

#define HEIGHT	700
#define WIDTH	700

# define WHITE	0xFFFFFF
# define GREY	0x555555
# define BLACK	0x111111
# define VIOLET	0xB545AE
# define BLUE	0x6692CC
# define GREEN	0x81CC66
# define ORANGE	0xED6205

#define K_UP	126
#define K_DOWN	125
#define K_LEFT	123
#define K_RIGHT	124
#define K_ESC	53
#define K_PLUS	69
#define K_MINUS	78
#define K_C		8
#define K_PUP	116
#define K_PDOWN	121
#define K_1		83
#define K_2		84

#define M_W_UP		5
#define M_W_DOWN	4

typedef struct	s_draw
{
	int			iter;
	int			color;
	double		zoom;
	double		move_x;
	double		move_y;
	double		p_r;	// real and imaginary part of p pixel
	double		p_i;	// real and imaginary part of p pixel
	double		c_r;	// real and imaginary part of c constant
	double		c_i;	// real and imaginary part of c constant
	double		new_r;	// real and imaginary part of new and old
	double		new_i;	// real and imaginary part of new and old
	double		old_r;	// real and imaginary part of new and old
	double		old_i;	// real and imaginary part of new and old
}				t_draw;

typedef struct	s_mlx
{
	int			id;
	int			bw;
	int			bpp;
	int			bypp;
	int			line;
	int			hooked;
	int			endian;
	int			mouse_x;
	int			mouse_y;
	void		*img;
	void		*win;
	void		*mlx;
	char		*data;
	t_draw		*draw;
}				t_mlx;

#endif
