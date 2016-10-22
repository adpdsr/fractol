/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:10:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/22 15:16:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	set_color_mode(int *a, int *b, int *c, int set)
{
	*a = (set == 1) ? 1 : 0;
	*b = (set == 2) ? 1 : 0;
	*c = (set == 3) ? 1 : 0;
}

static void	color_mode(t_mlx *mlx, int kc)
{
	if (kc == K_1)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 1);
	else if (kc == K_2)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 2);
	else if (kc == K_3)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 3);
	else if (kc == K_4)
		mlx->draw->color = CYAN;
	else if (kc == K_5)
		mlx->draw->color = BLUE;
	else if (kc == K_6)
		mlx->draw->color = VIOLET;
	else if (kc == K_7)
		mlx->draw->color = ORANGE;
	else if (kc == K_8)
		mlx->draw->color = YELLOW;
	else if (kc == K_9)
		mlx->draw->color = BROWN;
	else if (kc == K_F)
		mlx->friz = ((mlx->friz) ? 0 : 1);
}

static void	arrow_moves(t_draw *draw, int keycode)
{
	if (keycode == K_RIGHT)
	{
		draw->a_r -= 10 * draw->zoom;
		draw->m_r -= 10 * draw->zoom;
	}
	else if (keycode == K_LEFT)
	{
		draw->a_r += 10 * draw->zoom;
		draw->m_r += 10 * draw->zoom;
	}
	else if (keycode == K_UP)
	{
		draw->a_i += 10 * draw->zoom;
		draw->m_i += 10 * draw->zoom;
	}
	else if (keycode == K_DOWN)
	{
		draw->a_i -= 10 * draw->zoom;
		draw->m_i -= 10 * draw->zoom;
	}
}

static void	change_frac(t_mlx *mlx, int kc)
{
	if (kc == K_B)
	{
		mlx->draw->color = CYAN;
		mlx->draw->maxval = 6.0;
		mlx->id = 'b';
	}
	else if (kc == K_D)
	{
		mlx->draw->c_r = -0.123;
		mlx->draw->c_i = -0.745;
		mlx->id = 'd';
	}
	else if (kc == K_J)
	{
		mlx->draw->c_r = -0.7;
		mlx->draw->c_i = 0.27;
		mlx->id = 'j';
	}
	else if (kc == K_M)
	{
		mlx->draw->maxval = 4.0;
		mlx->id = 'm';
	}
}

int			hook_key(int kc, t_mlx *mlx)
{
	mlx->refresh = 1;
	if (kc == K_ESC)
		exit(0);
	else if (kc == K_PLUS || kc == K_MINUS)
		mlx->draw->iter += ((kc == K_PLUS) ? 1 : -1);
	else if (kc == K_PUP || kc == K_PDOWN)
		mlx->draw->zoom /= ((kc == K_PUP) ? 1.1 : 0.9);
	else if (kc == K_RIGHT || kc == K_LEFT || kc == K_UP || kc == K_DOWN)
		arrow_moves(mlx->draw, kc);
	else if ((kc > 82 && kc < 90) || (kc > 91 && kc < 93) || kc == K_F)
		color_mode(mlx, kc);
	else if (kc == K_B || kc == K_D || kc == K_J || kc == K_M)
		change_frac(mlx, kc);
	else
		mlx->refresh = 0;
	return (0);
}
