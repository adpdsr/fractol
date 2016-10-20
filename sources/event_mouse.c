/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:41:26 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:08:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	zoom(int x, int y, double zoom, t_mlx *mlx)
{
	double	x2;
	double	y2;

	mlx->draw->zoom *= zoom;
	x2 = ((double)x - (WIDTH / 2.0)) / (WIDTH / 2);
	y2 = ((double)y - (HEIGHT / 2.0)) / (HEIGHT / 2);
	mlx->draw->x += x2 / mlx->draw->zoom / 10;
	mlx->draw->y += y2 / mlx->draw->zoom / 10;
	return (1);
}

int			hook_mouse_button(int button, int x, int y, t_mlx *mlx)
{
	mlx->hooked = 1;
	if (button == M_W_UP)
		return (zoom(x, y, 1.1, mlx));
	else if (button == M_W_DOWN)
		return (zoom(x, y, 0.9, mlx));
	return (0);
}

int			hook_mouse_motion(int x, int y, t_mlx *mlx)
{
	if (mlx->friz == 0)
	{
		if (mlx->mouse_x != -1 && mlx->id == 'j')
		{
			mlx->draw->c_r += ((double)mlx->mouse_y - (double)y) / 300.0;
			mlx->draw->c_i += ((double)mlx->mouse_x - (double)x) / 300.0;
			mlx->hooked = 1;
		}
	}
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

int			hook_expose(t_mlx *mlx)
{
	draw_fractal(mlx, mlx->id);
	return (0);
}

int			loop_hook(t_mlx *mlx)
{
	if (mlx->hooked)
	{
		bzero(mlx->data, WIDTH * HEIGHT * (mlx->bpp / 8));
		draw_fractal(mlx, mlx->id);
	}
	mlx->hooked = 0;
	return (0);
}
