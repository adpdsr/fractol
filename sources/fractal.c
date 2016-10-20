/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 14:57:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:08:47 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	frac_julia(t_draw *draw, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	draw->z_r = (x + draw->m_r - WIDTH / 2) * draw->zoom + draw->a_r;
	draw->z_i = (y + draw->m_i - HEIGHT / 2) * draw->zoom + draw->a_i;
	while (i++ < draw->iter && (draw->z_r * draw->z_r + draw->z_i * draw->z_i) < 4.0)
	{
		tmp = draw->z_r;
		draw->z_r = draw->z_r * draw->z_r - draw->z_i * draw->z_i + draw->c_r;
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
	while (i++ < draw->iter && (draw->z_r * draw->z_r + draw->z_i * draw->z_i) < 4.0)
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
	draw->c_r = -0.123;
	draw->c_i = -0.745;
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
	if (id == 'd')
		frac_douady(draw, x, y);
	else if (id == 'm')
		frac_mandel(draw, x, y);
	else if (id == 'j')
		frac_julia(draw, x, y);
}
