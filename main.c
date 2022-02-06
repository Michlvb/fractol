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
double  complex(double coord, double size, t_data *data)
{
	double	value;

	value = (data->re_min + (coord / size) * (data->re_max - data->re_min));
	return (value);
}

int	render_frames(t_data *data)
{
	int		x;
	int		y;
	int     n;
	double  a;
	double	b;
	double  aa;
	double  bb;
	double	ca;
	double	cb;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			a = complex(x, WIDTH, data); //Complex reel
			b = complex(y, HEIGHT, data); //Complex imaginary
			ca = a;
			cb = b;
			n = 0;
			while (n < MAX_ITER)
			{
				aa = a*a - b*b;	
				bb = 2 * a * b;

				a = aa + ca;
				b = bb + cb;

				if (fabs(a + b) > 4)
				{
					break ;
				}
				n++;
			}
			if (n == MAX_ITER)
			{
				my_mlx_pixel_put(data, x, y, 0);
			} else {
				my_mlx_pixel_put(data, x, y, color_palette(n));
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
	frac->data.re_min = interpolate(m_re, frac->data.re_min, interp);
	frac->data.im_min = interpolate(m_im, frac->data.im_min, interp);
	frac->data.re_max = interpolate(m_re, frac->data.re_max, interp);
	frac->data.im_max = interpolate(m_im, frac->data.im_max, interp);
}

int	zoom_control(int keycode, t_vars *frac)
{
	if (keycode == 5)
	{
		frac->pos.interp = 1.0/1.03;
		// zoom(frac, fra)
		// zoom(frac, frac->mouse.Re, frac->mouse.Im, (1.0/1.03));
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
	fractal->data.im_min = -2.0;
	fractal->data.re_min = -2.0;
	// Calculate based on the screen ratio, to avoid image distortion when the display window ins't a square.
	fractal->data.im_max = fractal->data.im_min + (fractal->data.re_max + fractal->data.re_min) * HEIGHT / WIDTH;
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
	mlx_mouse_hook(vars.win, zoom_control, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop_hook(vars.mlx, render_frames, &vars.data);
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