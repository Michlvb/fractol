/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fractal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 16:15:58 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/02 20:46:39 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	map_complex(double x, double y, t_data *data, int check_julia)
{
	data->c_re = (data->re_min + (x / WIDTH) * (data->re_max - data->re_min));
	data->c_im = (data->im_min + (y / HEIGHT) * (data->im_max - data->im_min));
	if (!check_julia)
	{
		data->save_re = data->c_re;
		data->save_im = data->c_im;
	}
}

void	calculate_set(t_data *data)
{
	double	aa;
	double	bb;

	aa = (data->c_re * data->c_re) - (data->c_im * data->c_im);
	bb = 2 * data->c_re * data->c_im;
	data->c_re = aa + data->save_re;
	data->c_im = bb + data->save_im;
}

int	ft_check_inf(t_fractal *fractal)
{
	int	n;

	n = 0;
	while (n < MAX_ITER)
	{
		calculate_set(&fractal->data);
		if (fractal->data.c_re * fractal->data.c_re + \
			fractal->data.c_im * fractal->data.c_im > 16.0)
			break ;
		n++;
	}
	return (n);
}

void	ft_my_pixel_put(t_fractal *frac, int x, int y, int color)
{
	char	*dst;

	dst = frac->data.addr + (y * frac->data.line_length + x \
		* (frac->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render_frames(t_fractal *fractal)
{
	int		x;
	int		y;
	int		n;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			map_complex(x, y, &fractal->data, fractal->julia);
			n = ft_check_inf(fractal);
			if (n == MAX_ITER)
				ft_my_pixel_put(fractal, x, y, 0);
			else
				ft_my_pixel_put(fractal, x, y, color_palette(n));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, \
	fractal->data.img, 0, 0);
	return (0);
}
