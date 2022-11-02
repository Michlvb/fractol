/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 16:33:19 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 11:55:45 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_board_input(int keycode, t_fractal *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	else if (keycode == 126)
		ft_operate_imagine('-', fractal);
	else if (keycode == 125)
		ft_operate_imagine('+', fractal);
	else if (keycode == 124)
		ft_operate_real('+', fractal);
	else if (keycode == 123)
		ft_operate_real('-', fractal);
	return (0);
}

int	close_window(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->win);
	exit(0);
	return (0);
}

void	zoom(t_fractal *fractal, double m_re, double m_im, double interp)
{
	double	re_range;
	double	im_range;

	re_range = (fractal->data.re_max - fractal->data.re_min) * interp;
	im_range = (fractal->data.im_max - fractal->data.im_min) * interp;
	fractal->data.re_min = m_re - re_range / 2;
	fractal->data.re_max = m_re + re_range / 2;
	fractal->data.im_min = m_im - im_range / 2;
	fractal->data.im_max = m_im + im_range / 2;
}

int	zoom_control(int keycode, int x, int y, t_fractal *fractal)
{
	double	zoom_factor;

	zoom_factor = 1.1;
	(void)x;
	(void)y;
	if (keycode == 5)
		zoom(fractal, fractal->mouse.re, fractal->mouse.im, 1.0 / zoom_factor);
	else if (keycode == 4)
		zoom(fractal, fractal->mouse.re, fractal->mouse.im, zoom_factor);
	return (0);
}

int	mouse_move(int x, int y, t_fractal *fractal)
{
	fractal->mouse.re = x / (WIDTH / \
		(fractal->data.re_max - fractal->data.re_min)) \
	+ fractal->data.re_min;
	fractal->mouse.im = y / (HEIGHT / \
		(fractal->data.im_max - fractal->data.im_min)) \
	+ fractal->data.im_min;
	return (0);
}
