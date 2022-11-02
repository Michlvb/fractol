/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 19:39:23 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 11:53:23 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include "ft_printf.h"

# define WIDTH 700
# define HEIGHT 700
# define MAX_ITER 100

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	re_max;
	double	re_min;
	double	im_min;
	double	im_max;
	double	c_re;
	double	c_im;
	double	save_re;
	double	save_im;
}	t_data;

typedef struct s_mouse {
	double	re;
	double	im;
}	t_mouse;

typedef struct s_fractal {
	void		*mlx;
	void		*win;
	int			julia;
	t_data		data;
	t_mouse		mouse;
}				t_fractal;

enum	e_events {
	KEYDOWN = 2,
	KEYUP = 3,
	MOUSEDOWN = 4,
	MOUSEUP = 5,
	MOUSEMOVE = 6,
	EXPOSE = 12,	
	DESTROY = 17
};

// Error functions
void	program_usage(void);

//Colors
int		color_palette(int range);

//Utils
int		ft_strcmp(char *s1, char *s2);
void	parse_input(t_fractal *fractal, char *argv[]);
double	ft_atof(char *str);

// Extra utils
int		ft_isdigit(int c);
int		ft_isspace(char c);
void	ft_operate_imagine(char sign, t_fractal *fractal);
void	ft_operate_real(char sign, t_fractal *fractal);

//Events
int		key_board_input(int keycode, t_fractal *fractal);
int		close_window(t_fractal *fractal);
void	zoom(t_fractal *fractal, double m_re, double m_im, double interp);
int		zoom_control(int keycode, int x, int y, t_fractal *fractal);
int		mouse_move(int x, int y, t_fractal *fractal);

//Draw fractal
void	map_complex(double x, double y, t_data *data, int check_julia);
void	calculate_set(t_data *data);
int		render_frames(t_fractal *fractal);
int		ft_check_inf(t_fractal *fractal);

//Main
void	init_fractal(t_fractal *fractal, char *re, char *im);
int		ft_validate_input(char *str);

#endif