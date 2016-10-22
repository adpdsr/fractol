/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:27:51 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/22 15:29:37 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		init_draw(t_draw *draw, int id)
{
	draw->x = 0;
	draw->y = 0;
	draw->z_r = 0;
	draw->z_i = 0;
	draw->a_r = 0;
	draw->a_i = 0;
	draw->m_r = 0;
	draw->m_i = 0;
	if (id == 'd')
	{
		draw->c_r = -0.123;
		draw->c_i = -0.745;
	}
	else
	{
		draw->c_r = -0.7;
		draw->c_i = 0.27;
	}
	draw->iter = 35;
	draw->zoom = 0.005;
	draw->maxval = (id == 'b') ? 6.0 : 4.0;
	draw->color = (id == 'b') ? CYAN : BROWN;
}

static t_mlx	*init_mlx(t_mlx *m, int id)
{
	m = ft_memalloc(sizeof(t_mlx));
	m->bw = 0;
	m->un = 0;
	m->nm = 1;
	m->id = id;
	m->friz = 1;
	m->refresh = 0;
	if (!(m->mlx = mlx_init()))
		exit(1);
	if (!(m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT)))
		exit(1);
	if (!(m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "Fractol")))
		exit(1);
	if (!(m->data = mlx_get_data_addr(m->img,\
		&(m->bpp), &(m->line), &(m->endian))))
		exit(1);
	mlx_loop_hook(m->mlx, loop_hook, m);
	mlx_hook(m->win, 12, (1L << 15), hook_expose, m);
	mlx_hook(m->win, 2, (1L << 0), hook_key, m);
	mlx_hook(m->win, 4, (1L << 2), hook_mouse_button, m);
	mlx_hook(m->win, 6, (1L << 6), hook_mouse_motion, m);
	m->mouse_x = -1;
	m->mouse_y = -1;
	return (m);
}

static void		display_usage(void)
{
	ft_putendl_fd("\nusage: ./fractol [b | d | m | j]\n", 2);
	ft_putendl_fd("-> b for Burning Ship", 2);
	ft_putendl_fd("-> d for Douady", 2);
	ft_putendl_fd("-> m for Mandelbrot", 2);
	ft_putendl_fd("-> j for Julia\n", 2);
	ft_putendl_fd("controls:\n", 2);
	ft_putendl_fd("up		-> move up", 2);
	ft_putendl_fd("down		-> move down", 2);
	ft_putendl_fd("left		-> move left", 2);
	ft_putendl_fd("right		-> move right", 2);
	ft_putendl_fd("escape		-> quit Fractol", 2);
	ft_putendl_fd("page up		-> zoom in (center)", 2);
	ft_putendl_fd("page down	-> zoom out (center)", 2);
	ft_putendl_fd("pavnum nums	-> change color modes", 2);
	ft_putendl_fd("+		-> increase iteration number", 2);
	ft_putendl_fd("-		-> decrease iteration number", 2);
	ft_putendl_fd("f		-> freeze/unfreeze motion", 2);
	ft_putendl_fd("b		-> display Burning Ship fractal", 2);
	ft_putendl_fd("d		-> display Douady fractal", 2);
	ft_putendl_fd("j		-> display Julia fractal", 2);
	ft_putendl_fd("m		-> display Mendelbrot fractal\n", 2);
	exit(1);
}

static int		check_param(int ac, char **av)
{
	char *frac;

	frac = "bdmj";
	if (ac == 2 && av[1][1] == '\0' && (av[1] = ft_strstr(frac, av[1])))
		return (av[1][0]);
	display_usage();
	return (0);
}

int				main(int ac, char **av)
{
	int			id;
	t_mlx		*mlx;
	t_draw		draw;

	if ((id = check_param(ac, av)))
	{
		mlx = NULL;
		mlx = init_mlx(mlx, id);
		init_draw(&draw, id);
		mlx->draw = &draw;
		draw_fractal(mlx, mlx->id);
		mlx_loop(mlx->mlx);
	}
	return (0);
}
