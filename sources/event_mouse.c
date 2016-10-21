/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:41:26 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/21 19:43:06 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			hook_mouse_button(int button, int x, int y, t_mlx *mlx)
{
	mlx->hooked = 1;
	mlx->draw->a_r += (x - WIDTH / 2) * mlx->draw->zoom / 2;
	mlx->draw->a_i += (y - HEIGHT / 2) * mlx->draw->zoom / 2;
	if (button == M_W_UP)
		mlx->draw->zoom /= 2;
	if (button == M_W_DOWN)
		mlx->draw->zoom *= 2;
	return (0);
}

int			hook_mouse_motion(int x, int y, t_mlx *mlx)
{
	if (mlx->friz == 0)
	{
		if (mlx->mouse_x != -1 && mlx->id != 'm')
		{
			mlx->draw->c_r += ((double)mlx->mouse_y - (double)y) / 300.0;
			mlx->draw->c_i += ((double)mlx->mouse_x - (double)x) / 300.0;
			mlx->hooked = 1;
		}
		else if (mlx->mouse_x != -1)
		{
			mlx->draw->maxval += ((double)mlx->mouse_x - (double)x) / 100;
			mlx->draw->iter -= (mlx->mouse_y - y) / 5;
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
