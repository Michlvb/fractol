/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fractal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:20:48 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/17 21:09:43 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//AKA mapping the fractal to the screen, except it is not in the middle yet
void  map_complex(double x, double y, t_data *data, int check_julia)
{
	data->c_re = (data->re_min + (x / WIDTH) * (data->re_max - data->re_min));
	data->c_im = (data->im_min + (y / HEIGHT) * (data->im_max - data->im_min));
	if (!check_julia)
	{
		data->save_re = data->c_re;
		data->save_im = data->c_im;		
	}
}

void	calculate_set(t_data *frac)
{
	double	aa;
	double	bb;

	aa = (frac->c_re * frac->c_re) - (frac->c_im * frac->c_im);
	bb = 2 * frac->c_re * frac->c_im;

	frac->c_re = aa + frac->save_re;
	frac->c_im = bb + frac->save_im; 
}

int	render_frames(t_vars *data)
{
	int		x;
	int		y;
	int     n;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			map_complex(x, y, &data->data, data->julia);
			n = 0;
			while (n < MAX_ITER)
			{
				calculate_set(&data->data);

				if (data->data.c_re * data->data.c_re + data->data.c_im * data->data.c_im > 4.0)
				{
					break ;
				}
				n++;
			}
			if (n == MAX_ITER)
			{
				mlx_pixel_put(data->mlx, data->win, x, y, 0);
			} else {
				// double smoothed = log2(log2(data->data.c_re * data->data.c_re + data->data.c_im * data->data.c_im) / 2);
				// int colorN = (int)(sqrt(n + 10 - smoothed) * 256) % 16;
				// double smooth = n + 1 - log(log(sqrt(data->data.c_re * data->data.c_re + data->data.c_im * data->data.c_im )))/log(2);
				// smooth /= MAX_ITER
				mlx_pixel_put(data->mlx, data->win, x, y, color_palette(n));
			}
			y++;
		}
		x++;
	}
	return (0);
}
