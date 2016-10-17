/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 12:27:51 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/10/17 20:49:39 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fractol.h"

static int	pixel_to_image(t_mlx *mlx, int x, int y, int c)
{
	int		offset;
	float	color;

	c = (c == 0) ? 1 : c;
	color = (float)c / (float)mlx->draw->iter;
	offset = (y * WIDTH + x) * mlx->bypp;
	if (mlx->bw)
	{
		mlx->data[offset] = ((c < mlx->draw->iter) ? color * 256 : 0);
		mlx->data[offset + 1] = ((c < mlx->draw->iter) ? color * 256 : 0);
		mlx->data[offset + 2] = ((c < mlx->draw->iter) ? color * 256 : 0);
	}
	else
	{
		c = ((c < mlx->draw->iter) ? c * BLUE : 0x111111);
		ft_memmove(mlx->data + offset, &c, mlx->bypp);
	}
	return (0);
}

void	set_to_zero(double *a, double *b, double *c, double *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

static void	do_f_julia(t_draw *draw, double x, double y)
{
	int		i;
	double	w;
	double	h;

	i = 0;
	w = WIDTH;
	h = HEIGHT;
	draw->new_r = 1.5 * (x - w / 2) / (draw->zoom * w) + draw->move_x;
	draw->new_i = (y - h / 2) / (draw->zoom * h) + draw->move_y;
	while (i < draw->iter)
	{
		draw->old_r = draw->new_r;
		draw->old_i = draw->new_i;
		draw->new_r = draw->old_r * draw->old_r - draw->old_i * draw->old_i + draw->c_r;
		draw->new_i = 2.0 * draw->old_r * draw->old_i + draw->c_i;
		if ((draw->new_r * draw->new_r + draw->new_i * draw->new_i) > 4)
			break ;
		i++;
	}
	draw->color = i;
}

static void	do_f_mandelbrot(t_draw *draw, double x, double y)
{
	int		i;
	double	w;
	double	h;

	i = 0;
	w = WIDTH;
	h = HEIGHT;
	draw->p_r = 1.5 * (x - w / 2) / (1 * draw->zoom * w) + draw->move_x;
	draw->p_i = (y - h / 2) / (1 * draw->zoom * h) + draw->move_y;
	set_to_zero(&draw->new_r, &draw->new_i, &draw->old_r, &draw->old_i);
	while (i < draw->iter)
	{
		draw->old_r = draw->new_r;
		draw->old_i = draw->new_i;
		draw->new_r = draw->old_r * draw->old_r - draw->old_i * draw->old_i + draw->p_r;
		draw->new_i = 2.0 * draw->old_r * draw->old_i + draw->p_i + draw->p_i;
		if ((draw->new_r * draw->new_r + draw->new_i * draw->new_i) > 4)
			break ;
		i++;
	}
	draw->color = i;
}

static void	do_fractal(t_mlx *mlx, int id)
{
	double x;
	double y;

	y = 0;
	while (y <= WIDTH)
	{
		x = 0;
		while (x <= HEIGHT)
		{
			if (id == 1)
				do_f_mandelbrot(mlx->draw, x, y);
			else if (id == 2)
				do_f_julia(mlx->draw, x, y);
			pixel_to_image(mlx, x, y, mlx->draw->color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

static void	display_param(void)
{
	ft_putendl_fd("usage: ./fractol -fractal_type\n", 2);
	ft_putendl_fd("-julia\n-mandelbrot\n-burning_ship", 2);
	exit(1);
}

static void	init_draw(t_draw *draw)
{
	draw->iter = 20;
	draw->zoom = 1;
	draw->color = BLUE;
	draw->move_x = 0;
	draw->move_y = 0;
	draw->p_r = 0;
	draw->p_i = 0;
	draw->c_r = -0.7;
	draw->c_i = 0.27015;
	draw->new_r = 0;
	draw->new_i = 0;
	draw->old_r = 0;
	draw->old_i = 0;
}

static int	check_param(int ac, char **av)
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
		else
		{
			display_param();
			return (0);
		}
	}
	return (0);
}

static int		expose_hook(t_mlx *mlx)
{
	do_fractal(mlx, mlx->id);
	return (0);
}

#include <stdio.h>

static int		key_hook(int keycode, t_mlx *mlx)
{
	printf("code = %d\n", keycode);
	if (keycode == K_RIGHT)
		mlx->draw->move_x += 0.1 / mlx->draw->zoom;
	else if (keycode == K_LEFT)
		mlx->draw->move_x -= 0.1 / mlx->draw->zoom;
	else if (keycode == K_UP)
		mlx->draw->move_y -= 0.1 / mlx->draw->zoom;
	else if (keycode == K_DOWN)
		mlx->draw->move_y += 0.1 / mlx->draw->zoom;
	else if (keycode == K_PLUS)
		mlx->draw->iter++;
	else if (keycode == K_MINUS)
		mlx->draw->iter--;
	else if (keycode == K_PUP) // zoom in
		mlx->draw->zoom += 0.1;
	else if (keycode == K_PDOWN) // zoom out
		mlx->draw->zoom -= 0.1;
	else if (keycode == K_C)
		mlx->bw = ((mlx->bw == 0) ? 1 : 0);
	else if (keycode == K_1)
		mlx->draw->color = BLUE;
	else if (keycode == K_2)
		mlx->draw->color = GREEN;
	else if (keycode == K_ESC)
		exit(0);
	mlx->hooked = 1;
	return (0);
}

static int	loop_hook(t_mlx *mlx)
{
	if (mlx->hooked)
	{
		bzero(mlx->data, WIDTH * HEIGHT * mlx->bypp);
		do_fractal(mlx, mlx->id);
	}
	mlx->hooked = 0;
	return (0);
}

static int	zoom(int x, int y, double zoom, t_mlx *mlx)
{
	double move_x;
	double move_y;

	mlx->draw->zoom *= zoom;
	move_x = ((double)x - (WIDTH / 2.0)) / (WIDTH / 2);
	move_y = ((double)y - (HEIGHT / 2.0)) / (HEIGHT / 2);
	mlx->draw->move_x += move_x / mlx->draw->zoom / 10;
	mlx->draw->move_y += move_y / mlx->draw->zoom / 10;
	return (1);
}

static int	mouse_button_hook(int button, int x, int y, t_mlx *mlx)
{
	printf("button = %d\n", button); // test
	mlx->hooked = 1;
	if (button == M_W_UP)
		return (zoom(x, y, 1.1, mlx));
	else if (button == M_W_DOWN)
		return (zoom(x, y, 0.9, mlx));
	return (0);
}

static int	mouse_motion_hook(int x, int y, t_mlx *mlx)
{
	if (mlx->mouse_x != -1 && mlx->id == 2)
	{
		mlx->draw->c_r += ((double)mlx->mouse_y - (double)y) / 300.0;
		mlx->draw->c_i += ((double)mlx->mouse_x - (double)x) / 300.0;
		mlx->hooked = 1;
	}
	mlx->mouse_x = x;
	mlx->mouse_y = y;
	return (0);
}

static void	init_mlx(t_mlx *mlx)
{
	mlx->hooked = 0;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FRACTOL");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->line), &(mlx->endian));
	mlx->bypp = mlx->bpp / 8;
	mlx_loop_hook(mlx->mlx, loop_hook, mlx);
	mlx_hook(mlx->win, 12, (1L<<15), expose_hook, mlx); // Expose, ExposureMask
	mlx_hook(mlx->win, 2, (1L<<0), key_hook, mlx); // KeyPress, KeyPressMak
	mlx_hook(mlx->win, 4, (1L<<2), mouse_button_hook, mlx); // ButtonPress, ButtonPressMask
	mlx_hook(mlx->win, 6, (1L<<6), mouse_motion_hook, mlx); // MotionNotify, PointerMotionMask
	mlx->mouse_x = -1;
	mlx->mouse_y = -1;
}

int			main(int ac, char **av)
{
	t_mlx	mlx;
	t_draw	draw;

	init_draw(&draw);
	mlx.draw = &draw;
	if ((mlx.id = check_param(ac, av)))
	{
		init_mlx(&mlx);
		do_fractal(&mlx, mlx.id);
		mlx_loop(mlx.mlx);
	}
	return (0);
}
