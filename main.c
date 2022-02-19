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
#include <stdlib.h>
#include <string.h>

int	color_palette(int range);
int Key_board_input(int keycode, t_vars *vars);
int close_window();
void	zoom(t_vars *frac, double m_re, double m_im, double interp);
int	zoom_control(int keycode, int x, int y, t_vars *frac);
int	mouse_move(int x, int y, t_vars *frac);
void  map_complex(double x, double y, t_data *data, int check_julia);
void	calculate_set(t_data *frac);
int		render_frames(t_vars *data);
int	ErrorMessage(void);
int	check_args(int argc, char *argv[], t_vars *vars);

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


// double	interpolate(double start, double end, double interp)
// {
// 	return (start + ((end - start) * interp));
// }

void	init(t_vars *fractal)
{
	fractal->data.re_max = HEIGHT / 100;
	fractal->data.re_min = -(HEIGHT / 100);
	fractal->data.im_min = -(WIDTH / 100);
	// Calculate based on the screen ratio, to avoid image distortion when the display window ins't a square.
	//fractal->data.im_min + (fractal->data.re_max - fractal->data.re_min) * HEIGHT / WIDTH;
	fractal->data.im_max = WIDTH / 100;
	fractal->pos.interp = 1.0;
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	enum	e_events event;

	event = DESTROY;

	if (!check_args(argc, argv, &vars))
		return (0);
	init(&vars);
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
