/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:27:51 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/29 14:13:22 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

static void	display_param(void)
{
	ft_putendl_fd("usage: ./fractol -fractal_type\n", 2);
	ft_putendl("-julia\n-mandelbrot\n-burning_ship");
	exit(1);
}

static t_env	*init_env(t_env *env)
{
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	return (env);
}

static int		check_param(int ac, char **av, t_env *env)
{
	if (ac != 2)
		display_param();
	else
	{
		if (!ft_strcmp(av[1], "-mandelbrot"))
			return (1);
		else if (!ft_strcmp(av[1], "-julia"))
			return (2);
		else if (!ft_strcmp(av[1], "-burning_ship"))
			return (3);
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		id;
	t_env 	*env;

	env = init_env(env);
	id = check_param(ac, av, env);
	do_fractal(env, id);
	return (0);
}
