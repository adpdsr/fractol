/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:28:01 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:07:41 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <mlx.h>
#include "../libft/libft.h"

#define HEIGHT	1000
#define WIDTH	1000

# define YELLOW	0xFFFF00
# define BROWN	0xCD853F
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
#define K_PUP	116
#define K_PDOWN	121
#define K_1		83
#define K_2		84
#define K_3		85
#define K_4		86
#define K_5		87
#define K_6		88
#define K_7		89
#define K_8		91
#define K_9		92
#define K_D		2
#define K_F		3
#define K_J		38
#define K_M		46

#define M_W_UP		5
#define M_W_DOWN	4

typedef struct	s_draw
{
	int			iter;
	int			iteri;
	int			color;
	double		x;
	double		y;
	double		z_r;
	double		z_i;
	double		c_r;
	double		c_i;
	double		m_r;	
	double		m_i;
	double		a_r;
	double		a_i;
	double		zoom;
}				t_draw;

typedef struct	s_mlx
{
	int			id;
	int			bw;
	int			un;
	int			nm;
	int			bpp;
	int			line;
	int			friz;
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

int				hook_expose(t_mlx *mlx);
int				loop_hook(t_mlx *mlx);
int				hook_key(int keycode, t_mlx *mlx);
int				hook_mouse_button(int button, int x, int y, t_mlx *mlx);
int				hook_mouse_motion(int x, int y, t_mlx *mlx);

void			draw_fractal(t_mlx *mlx, int id);
void			select_fractal(t_draw *draw, int id, int x, int y);

#endif
