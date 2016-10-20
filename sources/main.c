/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:27:51 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/20 20:08:26 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	init_draw(t_draw *draw)
{
	draw->x = -1;
	draw->y = -1;
	draw->z_r = 0;
	draw->z_i = 0;
	draw->c_r = -0.7;
	draw->c_i = 0.27;
	draw->m_r = 0;
	draw->m_i = 0;
	draw->a_r = 0;
	draw->a_i = 0;
	draw->zoom = 0.005;
	draw->iter = 50;
	draw->color = BLUE;
}

static t_mlx	*init_mlx(t_mlx *mlx, int id)
{
	mlx = ft_memalloc(sizeof(t_mlx));
	mlx->bw = 0;
	mlx->un = 0;
	mlx->nm = 1;
	mlx->id = id;
	mlx->friz = 1;
	mlx->hooked = 0;
	if (!(mlx->mlx = mlx_init()))
	{
		ft_putendl("mlx_init failed");
		exit(1);
	}
	if (!(mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)))
	{
		ft_putendl("mlx_new_image failed");
		exit(1);
	}
	if (!(mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fractol")))
	{
		ft_putendl("mlx_new_window failed");
		exit(1);
	}
	if (!(mlx->data = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->line), &(mlx->endian))))
	{
		ft_putendl("mlx_get_data_adress failed");
		exit(1);
	}
	mlx_loop_hook(mlx->mlx, loop_hook, mlx);
	mlx_hook(mlx->win, 12, (1L<<15), hook_expose, mlx);
	mlx_hook(mlx->win, 2, (1L<<0), hook_key, mlx);
	mlx_hook(mlx->win, 4, (1L<<2), hook_mouse_button, mlx);
	mlx_hook(mlx->win, 6, (1L<<6), hook_mouse_motion, mlx);
	mlx->mouse_x = -1;
	mlx->mouse_y = -1;
	return (mlx);
}

static void	display_usage(void)
{
	ft_putendl_fd("\nusage: ./fractol [d | m | j]\n", 2);
	ft_putendl_fd("-> d for Douady", 2);
	ft_putendl_fd("-> m for Mandelbrot", 2);
	ft_putendl_fd("-> j for Julia\n", 2);
	exit(1);
}

static int	check_param(int ac, char **av)
{
	char frac[3] = "dmj";

	if (ac == 2 && av[1][1] == '\0' && (av[1] = ft_strstr(frac, av[1])))
		return (av[1][0]);
	display_usage();
	return (0);
}

int			main(int ac, char **av)
{
	int		id;
	t_mlx	*mlx;
	t_draw	draw;

	if ((id = check_param(ac, av)))
	{
		mlx = NULL;
		mlx = init_mlx(mlx, id);
		init_draw(&draw);
		mlx->draw = &draw;
		draw_fractal(mlx, mlx->id);
		mlx_loop(mlx->mlx);
	}
	return (0);
}
