/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:20:48 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/17 21:04:12 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	Key_board_input(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 126)
	{
		vars->data.im_max += 0.1;
		vars->data.im_min += 0.1;
	}
	else if (keycode == 125)
	{
		vars->data.im_max -= 0.1;
		vars->data.im_min -= 0.1;
	}
	else if (keycode == 123)
	{
		vars->data.re_min += 0.1;
		vars->data.re_max += 0.1;
	}
	else if (keycode == 124)
	{
		vars->data.re_max -= 0.1;
		vars->data.re_min -= 0.1;
	}
	return (0);
}

int	close_window(void)
{
	exit(0);
	return (0);
}

void	zoom(t_vars *frac, double m_re, double m_im, double interp)
{
	double	re_range;
	double	im_range;

	re_range = (frac->data.re_max - frac->data.re_min) * interp;
	im_range = (frac->data.im_max - frac->data.im_min) * interp;
	frac->data.re_min = m_re - re_range / 2;
	frac->data.re_max = m_re + re_range / 2;
	frac->data.im_min = m_im - im_range / 2;
	frac->data.im_max = m_im + im_range / 2;

}

int	zoom_control(int keycode, int x, int y, t_vars *frac)
{
	double	zoom_factor;
	double	*interp;

	interp = &frac->pos.interp;
	zoom_factor = 1.1;
	if (keycode == 5)
	{
		*interp /= zoom_factor;
		zoom(frac, frac->mouse.Re, frac->mouse.Im, 1.0 / zoom_factor);
		printf("CHECK FRAC: %d\n", x);
		printf("CHECK FRAC: %d\n", y);
		printf("CHECK RE_MIN AFTER ZOOM: %f\n", frac->data.re_min);
	}
	else if (keycode == 4)
	{
		*interp += zoom_factor;
		zoom(frac, frac->mouse.Re, frac->mouse.Im, zoom_factor);
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *frac)
{
	frac->mouse.Re = x / (WIDTH / (frac->data.re_max - frac->data.re_min)) \
	+ frac->data.re_min;
	frac->mouse.Im = y / (HEIGHT / (frac->data.im_max - frac->data.im_min)) \
	+ frac->data.im_min;
	return (0);
}
