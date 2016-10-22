/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:28:01 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/22 15:15:51 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include "./binders.h"
# include "../libft/libft.h"

typedef struct			s_draw
{
	int					iter;
	int					iteri;
	int					color;
	double				x;
	double				y;
	double				z_r;
	double				z_i;
	double				a_r;
	double				a_i;
	double				c_r;
	double				c_i;
	double				m_r;
	double				m_i;
	double				zoom;
	double				maxval;
}						t_draw;

typedef struct			s_mlx
{
	int					id;
	int					bw;
	int					un;
	int					nm;
	int					bpp;
	int					line;
	int					friz;
	int					endian;
	int					refresh;
	int					mouse_x;
	int					mouse_y;
	void				*img;
	void				*win;
	void				*mlx;
	char				*data;
	t_draw				*draw;
}						t_mlx;

int						hook_expose(t_mlx *mlx);
int						loop_hook(t_mlx *mlx);
int						hook_key(int keycode, t_mlx *mlx);
int						hook_mouse_button(int button, int x, int y, t_mlx *mlx);
int						hook_mouse_motion(int x, int y, t_mlx *mlx);

void					draw_fractal(t_mlx *mlx, int id);
void					select_fractal(t_draw *draw, int id, int x, int y);

#endif
