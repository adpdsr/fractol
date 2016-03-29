/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_f_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 16:01:19 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/29 19:19:34 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

void	do_f_julia(t_env *env)
{
	int		x;
	int		y;
	int 	j;
	int 	k;
	t_coord	**pixel;
	double  x1;
	double  y1;
	double  x2;
	double  y2;
	int     img_x;
	int     img_y;
	int		zoom;
	int		iter;
	double  c_r;
	double  c_i;
	double  z_r;
	double  z_i;
	double	tmp;
	double	i;

	x1 = -2.1;
	y1 = -1.2;
	x2 = 0.6;
	y2 = 1.2;
	zoom = 100;
	iter = 100;
	img_x = (x2 - x1) * zoom;
	img_y = (y2 - y1) * zoom;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, img_x, img_y, "| FRACTOL |");
	if (!(pixel = (t_coord **)malloc(sizeof(t_coord *) * img_y)))
		exit(1);
	j = 0;
	while (j < img_y)
	{
		if (!(pixel[j] = (t_coord *)malloc(sizeof(t_coord) * img_x)))
			exit (1);
		k = 0;
		while (k < img_x)
		{
			pixel[j][k].x = 0;
			pixel[j][k].y = 0;
			k++;
		}
		j++;
	}
	x = 0;
	while (x < img_y)
	{
		y = 0;
		while (y < img_x)
		{
			c_r = x / zoom + x1;
			c_i = y / zoom + y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (i < iter && (z_r * z_r + z_i * z_i) < 4)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = (2 * z_i * tmp) + c_i;
				pixel[x][y].x = (z_r - x1) * zoom;
				pixel[x][y].y = (z_i - y1) * zoom;
				i++;
			}
			if (i != iter)
			{
				j = 0;
				while (j < img_y)
				{
					k = 0;
					while (k < img_x)
					{
						if (pixel[j][k].x != 0 && pixel[j][k].y != 0)
						{
					//		pixel[j][k].x += 1;
					//		pixel[j][k].y += 1;
						}
						k++;
					}
					j++;
				}
			}
			y++;
		}
		x++;
	}
	j = 0;
	while (j < img_y)
	{
		k = 0;
		while (k < img_x)
		{
			mlx_pixel_put(env->win, env->win, pixel[j][k].x, pixel[j][k].y, 0x00FFFFFF);
			k++;
		}
		j++;
	}
	mlx_loop(env->mlx);
}
