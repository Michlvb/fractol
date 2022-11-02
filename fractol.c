/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:14:07 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/31 16:03:45 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	ft_validate_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && \
			(str[i] != '-' && str[i] != '+' && str[i] != '.'))
			return (0);
		i++;
	}
	return (1);
}

void	init_fractal(t_fractal *fractal, char *re, char *im)
{
	fractal->data.re_max = HEIGHT / 100;
	fractal->data.re_min = -(HEIGHT / 100);
	fractal->data.im_min = -(WIDTH / 100);
	fractal->data.im_max = WIDTH / 100;
	if (fractal->julia)
	{
		if (!ft_validate_input(re) || !ft_validate_input(im))
			program_usage();
		fractal->data.save_re = ft_atof(re);
		fractal->data.save_im = ft_atof(im);
	}
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "FRACTAL");
	fractal->data.img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->data.addr = mlx_get_data_addr(fractal->data.img, \
											&fractal->data.bits_per_pixel, \
											&fractal->data.line_length, \
											&fractal->data.endian);
}

int	main(int argc, char *argv[])
{
	t_fractal		fractal;

	if (argc < 2)
		program_usage();
	parse_input(&fractal, argv);
	init_fractal(&fractal, argv[2], argv[3]);
	mlx_hook(fractal.win, KEYDOWN, 1L << 0, key_board_input, &fractal);
	mlx_hook(fractal.win, DESTROY, 0, close_window, &fractal);
	mlx_hook(fractal.win, MOUSEMOVE, 0, mouse_move, &fractal);
	mlx_hook(fractal.win, 4, 0, zoom_control, &fractal);
	mlx_loop_hook(fractal.mlx, render_frames, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
