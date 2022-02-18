/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 09:39:19 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/17 21:09:23 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <math.h>

int	color_palette(int range);
int Key_board_input(int keycode, t_vars *vars);
int close_window();
void	zoom(t_vars *frac, double m_re, double m_im, double interp);
int	zoom_control(int keycode, int x, int y, t_vars *frac);
int	mouse_move(int x, int y, t_vars *frac);
void  map_complex(double x, double y, t_data *data, int check_julia);
void	calculate_set(t_data *frac);
int		render_frames(t_vars *data);

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

int	ErrorMessage(void)
{
	printf("Incorrect input\n");
	printf("The following Fractal sets are available:\n");
	printf("- Julia\n");
	printf("- Mandelbrot\n");
	return (0);
}

// double	interpolate(double start, double end, double interp)
// {
// 	return (start + ((end - start) * interp));
// }


void	init(t_vars *fractal, double re, double im)
{
	fractal->data.re_max = HEIGHT / 100;
	fractal->data.re_min = -(HEIGHT / 100);
	fractal->data.im_min = -(WIDTH / 100);
	// Calculate based on the screen ratio, to avoid image distortion when the display window ins't a square.
	//fractal->data.im_min + (fractal->data.re_max - fractal->data.re_min) * HEIGHT / WIDTH;
	fractal->data.im_max = WIDTH / 100;
	if(fractal->julia)
	{
		fractal->data.save_re = re;
		fractal->data.save_im = im;
	}
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
		vars.julia = 0;
	else if (ft_strcmp(argv[1], "julia") == 0 || \
			ft_strcmp(argv[1], "Julia") == 0)
		vars.julia = 1;
	else
		return (ErrorMessage());
	init(&vars, -0.7269, 0.1889);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FRACTAL");
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	mlx_hook(vars.win, KEYDOWN, 1L << 0, Key_board_input, &vars);
	mlx_hook(vars.win, DESTROY, 0, close_window, &vars);
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