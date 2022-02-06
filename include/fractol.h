/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:20:48 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/04 17:15:24 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>

# define WIDTH 700
# define HEIGHT 700
# define START	-2.0
# define END	2.0
# define MAX_ITER 100

typedef struct s_coord {
	double	shift_x;
	double	shift_y;
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
}	t_data;

typedef struct s_mouse {
	double	Re;
	double	Im;
}	t_mouse;

typedef struct s_vars {
	void		*mlx;
	void		*win;
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
double	complex(double coord, double size, t_data *data);
int		render_frames(t_data *data);
int		close(int keycode, t_vars *vars);

#endif