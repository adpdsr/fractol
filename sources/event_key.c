/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:10:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:08:00 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		set_color_mode(int *a, int *b, int *c, int set)
{
	*a = (set == 1) ? 1 : 0;
	*b = (set == 2) ? 1 : 0;
	*c = (set == 3) ? 1 : 0;
}

#include <stdio.h>

int		hook_key(int keycode, t_mlx *mlx)
{
	printf("keycode = %d\n", keycode);
	mlx->hooked = 1;
	// moves
	if (keycode == K_RIGHT)
		mlx->draw->m_r -= 50;
	else if (keycode == K_LEFT)
		mlx->draw->m_r += 50;
	else if (keycode == K_UP)
		mlx->draw->m_i += 50;
	else if (keycode == K_DOWN)
		mlx->draw->m_i -= 50;

	// iterations
	else if (keycode == K_PLUS)
		mlx->draw->iter++;
	else if (keycode == K_MINUS)
		mlx->draw->iter--;

	// zooms
	else if (keycode == K_PUP)
		mlx->draw->zoom /= 1.1;
	else if (keycode == K_PDOWN)
		mlx->draw->zoom *= 1.1;

	// modes and colors
	else if (keycode == K_1)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 1);
	else if (keycode == K_2)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 2);
	else if (keycode == K_3)
		set_color_mode(&mlx->nm, &mlx->bw, &mlx->un, 3);
	else if (keycode == K_4)
		mlx->draw->color = BLUE;
	else if (keycode == K_5)
		mlx->draw->color = GREEN;
	else if (keycode == K_6)
		mlx->draw->color = VIOLET;
	else if (keycode == K_7)
		mlx->draw->color = ORANGE;
	else if (keycode == K_8)
		mlx->draw->color = YELLOW;
	else if (keycode == K_9)
		mlx->draw->color = BROWN;
	else if (keycode == K_F)
		mlx->friz = ((mlx->friz) ? 0 : 1);

	// escape
	else if (keycode == K_ESC)
		exit(0);

	// fractal id
	else if (keycode == K_D)
		mlx->id = 'd';
	else if (keycode == K_J)
		mlx->id = 'j';
	else if (keycode == K_M)
		mlx->id = 'm';
	else
		mlx->hooked = 0;
	printf ("friz = %d\n", mlx->friz);
	return (0);
}
