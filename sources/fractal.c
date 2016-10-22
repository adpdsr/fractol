/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 14:57:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/22 15:16:53 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	frac_burnin(t_draw *d, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	d->z_r = 0;
	d->z_i = 0;
	d->c_r = (x + d->m_r - WIDTH / 2) * d->zoom + d->a_r;
	d->c_i = (y + d->m_i - HEIGHT / 2) * d->zoom + d->a_i;
	while (i++ < d->iter && (pow(d->z_r, 2) + pow(d->z_i, 2) < d->maxval))
	{
		tmp = d->z_r;
		d->z_r = 2 * fabs(d->z_r * d->z_i) + d->c_i;
		d->z_i = d->z_i * d->z_i - tmp * tmp - d->c_r;
		i++;
	}
	d->iteri = i;
}

static void	frac_julia(t_draw *d, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	d->z_r = (x + d->m_r - WIDTH / 2) * d->zoom + d->a_r;
	d->z_i = (y + d->m_i - HEIGHT / 2) * d->zoom + d->a_r;
	while (i++ < d->iter && (d->z_r * d->z_r + d->z_i * d->z_i) < 4.0)
	{
		tmp = d->z_r;
		d->z_r = pow(d->z_r, 2) - pow(d->z_i, 2) + d->c_r;
		d->z_i = 2 * d->z_i * tmp + d->c_i;
	}
	d->iteri = i;
}

static void	frac_mandel(t_draw *d, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	d->z_r = 0;
	d->z_i = 0;
	d->c_r = (x + d->m_r - WIDTH / 2) * d->zoom + d->a_r;
	d->c_i = (y + d->m_i - HEIGHT / 2) * d->zoom + d->a_i;
	while (i++ < d->iter && (d->z_r * d->z_r + d->z_i * d->z_i) < d->maxval)
	{
		tmp = d->z_r;
		d->z_r = d->z_r * d->z_r - d->z_i * d->z_i + d->c_r;
		d->z_i = 2 * d->z_i * tmp + d->c_i;
	}
	d->iteri = i;
}

static void	frac_douady(t_draw *d, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	d->z_r = (x + d->m_r - WIDTH / 2) * d->zoom + d->a_r;
	d->z_i = (y + d->m_i - HEIGHT / 2) * d->zoom + d->a_i;
	while (i++ < d->iter && (d->z_r * d->z_r + d->z_i * d->z_i) < 8.0)
	{
		tmp = d->z_r;
		d->z_r = d->z_r * d->z_r - d->z_i * d->z_i + d->c_r;
		d->z_i = 2 * d->z_i * tmp + d->c_i;
		i++;
	}
	d->iteri = i;
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
