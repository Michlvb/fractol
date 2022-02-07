/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 09:39:19 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/04 17:24:42 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"
#include <stdio.h>
#include <math.h>

int	color_palette(int range);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

//AKA mapping the fractal to the screen, except it is not in the middle yet
void  map_complex(double x, double y, t_data *data)
{
	data->c_re = (data->re_min + (x / WIDTH) * (data->re_max - data->re_min));
	data->c_im = (data->im_min + (y / HEIGHT) * (data->im_max - data->im_min));
	data->save_re = data->c_re;
	data->save_im = data->c_im;
}

int	render_frames(t_vars *data)
{
	int		x;
	int		y;
	int     n;
	double  aa;
	double  bb;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			map_complex(x, y, &data->data);
			n = 0;
			while (n < MAX_ITER)
			{
				aa = data->data.c_re*data->data.c_re - data->data.c_im*data->data.c_im;	
				bb = 2 * data->data.c_re * data->data.c_im;

				data->data.c_re = aa + data->data.save_re;
				data->data.c_im = bb + data->data.save_im;

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
				mlx_pixel_put(data->mlx, data->win, x, y, color_palette(n));
			}
			y++;
		}
		x++;
	}
	return (0);
}

//Destroys window
int	close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	ErrorMessage(void)
{
	printf("Incorrect input\n");
	printf("The following Fractal sets are available:\n");
	printf("- Julia\n");
	printf("- Mandelbrot\n");
	return (0);
}

double	interpolate(double start, double end, double interp)
{
	return (start + ((end - start) * interp));
}

void	zoom(t_vars *frac, double m_re, double m_im, double interp)
{
	double re_range = (frac->data.re_max - frac->data.re_min) * interp;
	double im_range = (frac->data.im_max - frac->data.im_min) * interp;

	frac->data.re_min = m_re - re_range / 2;
	frac->data.re_max = m_re + re_range / 2;
	frac->data.im_min = m_im - im_range / 2;
	frac->data.im_max = m_im + im_range / 2;

	// interp = 0.1;
	// frac->data.re_min = interpolate(m_re, frac->data.re_min, interp);
	// frac->data.im_min = interpolate(m_im, frac->data.im_min, interp);
	// frac->data.re_max = interpolate(m_re, frac->data.re_max, interp);
	// frac->data.im_max = interpolate(m_im, frac->data.im_max, interp);
}

int	zoom_control(int keycode, int x, int y, t_vars *frac)
{
	double	zoom_factor;
	double	*interp;

	interp = &frac->pos.interp;
	zoom_factor = 1.03;
	printf("CHECK RE_MIN BEFORE ZOOM: %f\n", frac->data.re_min);
	if (keycode == 5)
	{
		*interp /= zoom_factor;
		zoom(frac, frac->mouse.Re, frac->mouse.Im, 1.0 / zoom_factor);
		printf("CHECK FRAC: %d\n", x);
		printf("CHECK FRAC: %d\n", y);
		printf("CHECK RE_MIN AFTER ZOOM: %f\n", frac->data.re_min);
		// frac->data.re_min = interpolate(m_re, frac->data.re_min, interp);
		// frac->data.im_min = interpolate(m_im, frac->data.im_min, interp);
		// frac->data.re_max = interpolate(m_re, frac->data.re_max, interp);
		// frac->data.im_max = interpolate(m_im, frac->data.im_max, interp);
	} else if (keycode == 4)
	{
		*interp += zoom_factor;
		zoom(frac, frac->mouse.Re, frac->mouse.Im, zoom_factor);
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *frac)
{
	frac->mouse.Re = x / (WIDTH / (frac->data.re_max - frac->data.re_min)) + frac->data.re_min;
	frac->mouse.Im = y / (HEIGHT / (frac->data.im_max - frac->data.im_min)) + frac->data.im_min;
	return (0);
}

void	init(t_vars *fractal)
{
	fractal->data.re_max = 2.0;
	fractal->data.re_min = -2.0;
	fractal->data.im_min = -2.0;
	// Calculate based on the screen ratio, to avoid image distortion when the display window ins't a square.
	fractal->data.im_max = fractal->data.im_min + (fractal->data.re_max - fractal->data.re_min) * HEIGHT / WIDTH;
	// fractal->data.im_max = HEIGHT / 100;
	fractal->pos.interp = 1.0;
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	enum	e_events event;

	event = DESTROY;
	if (argc < 2)
		return (ErrorMessage());
	else if (ft_strcmp(argv[1], "mandelbrot") == 0 || \
			ft_strcmp(argv[1], "Mandelbrot") == 0)
		printf("DISPLAYING MANDELBROT\n");
	else if (ft_strcmp(argv[1], "julia") == 0 || \
			ft_strcmp(argv[1], "Julia") == 0)
		printf("DISPLAYING JULIA\n");
	else
		return (ErrorMessage());
	init(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FRACTAL");
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	mlx_hook(vars.win, KEYDOWN, 1L << 0, close, &vars);
	mlx_hook(vars.win, MOUSEMOVE, 0, mouse_move, &vars);
	mlx_hook(vars.win, 4, 0, zoom_control, &vars);
	mlx_loop_hook(vars.mlx, render_frames, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop(vars.mlx);
}

/*
Program Flow:

//apply the formula c = a^2 - b^2 + 2abi

1. Ask which set the user want Mandelbrot or Julia via the command line.
2. Display chosen set
3. Setup keyboard events
	// img.img = mlx_new_image(vars.mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// // while(width < 10)
	// {
	// 	i = 0;
	// 	while (height < 10)
	// 	{
	// 		my_mlx_pixel_put(&img, 5+i, 5, 0x00FF0000);
	// 		my_mlx_pixel_put(&img, 5, 5+i, 0x00FF0000);
	// 		height++;
	// 		i++;
	// 	}
	// 	my_mlx_pixel_put(&img, 5+i, 15, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 15, 5+i, 0x00FF0000);
	// 	// my_mlx_pixel_put(&img, 5, 5+i, 0x00FF0000);
	// 	// my_mlx_pixel_put(&img, 5, 15+i, 0x00FF0000);
	// 	// my_mlx_pixel_put(&img, 15+i, 5, 0x00FF0000);
	// 	width++;
	// }

0x00FF0000 - red
0x4287f5 - blue 
0x00c738 - green
*/