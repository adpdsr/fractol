/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_f_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 13:01:39 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/29 19:19:38 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void	do_f_mandelbrot(t_env *env)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	zoom_x;
	double	zoom_y;
	int		iter;
	int		img_x;
	int		img_y;
	int		x;
	int		y;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	double	i;

	x1 = -2.1;
	y1 = -1.2;
	x2 = 0.6;
	y2 = 1.2;
	img_x = 270;
	img_y = 240;
	iter = 50;
	zoom_x = img_x / (x2 -x1);
	zoom_y = img_y /(y2 -y1);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, img_x, img_y, "| FRACTOL |");
	x = 0;
	while (x < img_x)
	{
		y = 0;
		while (y < img_y)
		{
			c_r = x / zoom_x + x1;
			c_i = y / zoom_y + y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while ((z_r * z_r + z_i * z_i) < 4 && i < iter)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = (2 * z_i * tmp) + c_i;
				i++;
			}
			if (i == iter)
				mlx_pixel_put(env->mlx, env->win, x, y, 0x00FFFFFF);
//			else
//				mlx_pixel_put(env->mlx, env->win, x, y, get_color(z_i));
			y++;
		}
		x++;
	}
	//mlx_key_hook(env->mlx, &hook_key, env);
	mlx_loop(env->mlx);
}
