/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 14:57:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/21 20:51:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	frac_burnin(t_draw *draw, int x, int y)
{
	int		i;

	i = 0;
	x = (x + draw->a_r) / draw->zoom;
	x = (x < 0) ? -x : x;
	y = (y + draw->a_i) / draw->zoom;
	y = (y < 0) ? -y : y;
	while ((x > 0 || y > 0) && i++ < draw->iter)
	{
		if (x % 3 == 1 && y % 3 == 1)
			break ;
		x /= 3;
		y /= 3;
	}
	draw->iteri = i;
}

static void	frac_julia(t_draw *draw, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	draw->z_r = (x + draw->m_r - WIDTH / 2) * draw->zoom + draw->a_r;
	draw->z_i = (y + draw->m_i - HEIGHT / 2) * draw->zoom + draw->a_r;
	while (i++ < draw->iter && (draw->z_r * draw->z_r + draw->z_i * draw->z_i) < 4.0)
	{
		tmp = draw->z_r;
		draw->z_r = pow(draw->z_r, 2) - pow(draw->z_i, 2) + draw->c_r;
		draw->z_i = 2 * draw->z_i * tmp + draw->c_i;
	}
	draw->iteri = i;
}

static void	frac_mandel(t_draw *draw, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	draw->z_r = 0;
	draw->z_i = 0;
	draw->c_r = (x + draw->m_r - WIDTH / 2) * draw->zoom + draw->a_r;
	draw->c_i = (y + draw->m_i - HEIGHT / 2) * draw->zoom + draw->a_i;
	while (i++ < draw->iter && (draw->z_r * draw->z_r + draw->z_i * draw->z_i) < draw->maxval)
	{
		tmp = draw->z_r;
		draw->z_r = draw->z_r * draw->z_r - draw->z_i * draw->z_i + draw->c_r;
		draw->z_i = 2 * draw->z_i * tmp + draw->c_i;
	}
	draw->iteri = i;
}

static void	frac_douady(t_draw *draw, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	draw->z_r = (x + draw->m_r - WIDTH / 2) * draw->zoom + draw->a_r;
	draw->z_i = (y + draw->m_i - HEIGHT / 2) * draw->zoom + draw->a_i;
	while (i++ < draw->iter && (draw->z_r * draw->z_r + draw->z_i * draw->z_i) < 8.0)
	{
		tmp = draw->z_r;
		draw->z_r = draw->z_r * draw->z_r - draw->z_i * draw->z_i + draw->c_r;
		draw->z_i = 2 * draw->z_i * tmp + draw->c_i;
		i++;
	}
	draw->iteri = i;
}

void		select_fractal(t_draw *draw, int id, int x, int y)
{
	if (id == 'b')
		frac_burnin(draw, x, y);
	else if (id == 'd')
		frac_douady(draw, x, y);
	else if (id == 'm')
		frac_mandel(draw, x, y);
	else if (id == 'j')
		frac_julia(draw, x, y);
}
