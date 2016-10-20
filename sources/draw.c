/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:22:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:08:36 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

typedef unsigned int uint;

static uint	ft_rgb(short r, short g, short b)
{
	uint color;

	color = 0;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	color = (color + r) << 8;
	color = (color + g) << 8;
	color = (color + b);
	return (color);
}

static void	pixel_put(t_mlx *mlx, int x, int y, uint color)
{
	int         i;
	char        c;

	if (mlx->data && x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		i = x * (mlx->bpp / 8) + mlx->line * y;
		if (mlx->endian == 0)
		{
			c = (color & 0xFF) >> 0;
			mlx->data[i] = c;
			c = (color & 0xFF00) >> 8;
			mlx->data[i + 1] = c;
			c = (color & 0xFF0000) >> 16;
			mlx->data[i + 2] = c;
		}
		else
		{
			c = (color & 0xFF0000) >> 16;
			mlx->data[i] = c;
			c = (color & 0xFF00) >> 8;
			mlx->data[i + 1] = c;
			c = (color & 0xFF) >> 0;
			mlx->data[i + 2] = c;
		}
	}
}

static void pixel_to_image(t_mlx *mlx, double x, double y, int c)
{
	int z;

	if (c == mlx->draw->iter)
		pixel_put(mlx, x, y, ft_rgb(256, 256, 256));
	else
	{
		if (mlx->bw)
		{
			z = (c < mlx->draw->iter) ? mlx->draw->color : 0;
			pixel_put(mlx, x, y, z);
		}
		else if (mlx->un)
		{
			z = (c < mlx->draw->iter) ? 0 : mlx->draw->color;
			pixel_put(mlx, x, y, z);
		}
		else
		{
			z = mlx->draw->iter - c;
			pixel_put(mlx, x, y, ft_rgb(z * 10, z * 20, z * 30));
		}
	}
}

void		draw_fractal(t_mlx *mlx, int id)
{
	int x;
	int y;

	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			select_fractal(mlx->draw, id, x, y);
			pixel_to_image(mlx, x, y, mlx->draw->iteri);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
