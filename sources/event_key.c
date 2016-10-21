/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:10:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/21 20:51:11 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		set_color_mode(int *a, int *b, int *c, int set)
{
	*a = (set == 1) ? 1 : 0;
	*b = (set == 2) ? 1 : 0;
	*c = (set == 3) ? 1 : 0;
}

static void		arrow_moves(t_draw *draw, int keycode)
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

int		hook_key(int kc, t_mlx *mlx)
{
	mlx->hooked = 1;
	
	// moves
	if (kc == K_RIGHT || kc == K_LEFT || kc == K_UP || kc == K_DOWN)
		arrow_moves(mlx->draw, kc);

	// iterations
	else if (kc == K_PLUS || kc == K_MINUS)
		mlx->draw->iter += ((kc == K_PLUS) ? 1 : -1);

	// zooms
	else if (kc == K_PUP || kc == K_PDOWN)
		mlx->draw->zoom /= ((kc == K_PUP) ? 1.1 : 0.9);

	// modes and colors
	else if (kc == K_1)
	{
		mlx->draw->color = YELLOW;
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 1);
	}
	else if (kc == K_2)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 2);
	else if (kc == K_3)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 3);
	else if (kc == K_4)
		mlx->draw->color = BLUE;
	else if (kc == K_5)
		mlx->draw->color = GREEN;
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

	// escape
	else if (kc == K_ESC)
		exit(0);

	// fractal id
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
		mlx->id = 'm';
	else
		mlx->hooked = 0;
	return (0);
}
