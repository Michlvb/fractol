/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:20:48 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/17 21:08:31 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

# define WIDTH 700
# define HEIGHT 700
# define START	-2.0
# define END	2.0
# define MAX_ITER 100

typedef struct s_coord {
	double	interp;
}	t_coord;

// typedef struct s_mandel {
// 	double	re_max;
// 	double	re_min;
// 	double	im_min;
// 	double	im_max;
// 	double	c_re;
// 	double	c_im;
// }	t_mandel

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
	double	Re;
	double	Im;
}	t_mouse;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	int			julia;
	t_data		data;
	t_coord		pos;
	t_mouse		mouse;
}				t_vars;

enum	e_events {
	KEYDOWN = 2,
	KEYUP = 3,
	MOUSEDOWN = 4,
	MOUSEUP = 5,
	MOUSEMOVE = 6,
	EXPOSE = 12,
	DESTROY = 17
};

int		color_palette(int range);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_strcmp(char *s1, char *s2);
void	map_complex(double x, double y, t_data *data, int check);
int		render_frames(t_vars *data);
int		Key_board_input(int keycode, t_vars *vars);
int		close_window(void);
void	zoom(t_vars *frac, double m_re, double m_im, double interp);
int		zoom_control(int keycode, int x, int y, t_vars *frac);
int		mouse_move(int x, int y, t_vars *frac);
void	calculate_set(t_data *frac);

#endif