/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 09:39:19 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/01 15:29:49 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"
#include <stdio.h>

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

int	render_frames(t_data *data)
{
	int		width;
	int		height;
	int		x;
	int		y;

	width = 500;
	height = 500;
	y = 100;
	while (y < height && y < 400)
	{
		x = 50;
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		while (x < width && x < 400)
		{
			my_mlx_pixel_put(data, x, y, 0x00FF0000);
			x++;
		}
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		y++;
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

int	display_startMessage(void)
{
	printf("Incorrect input\n");
	printf("The following Fractal sets are available:\n");
	printf("- Julia\n");
	printf("- Mandelbrot\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	// int		i;
	enum	e_events event;

	event = DESTROY;
	if (argc < 2)
		return (display_startMessage());
	else if (ft_strcmp(argv[1], "mandelbrot") == 0 || \
			ft_strcmp(argv[1], "Mandelbrot") == 0)
		printf("DISPLAYING MANDELBROT\n");
	else if (ft_strcmp(argv[1], "julia") == 0 || \
			ft_strcmp(argv[1], "Julia") == 0)
		printf("DISPLAYING JULIA\n");
	else
		return (display_startMessage());
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "FRACTOL");
	vars.data.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	//Now, we have an image but how exactly do we write pixels to this? For this we need to get the memory address on which we will mutate the bytes accordingly. 
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	mlx_hook(vars.win, KEYDOWN, 1L << 0, close, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop_hook(vars.mlx, render_frames, &vars.data);
	mlx_loop(vars.mlx);
}

/*
Program Flow:

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