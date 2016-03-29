/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:41:14 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/29 19:19:36 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	do_fractal(t_env *env, int id)
{
	if (id == 1)
		do_f_mandelbrot(env);
	else if (id == 2)
		do_f_julia(env);
//	else if (id == 3)
//		do_f_burning_ship(env);
}
