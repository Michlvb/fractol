/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 13:51:37 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 11:03:12 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	ft_operate_imagine(char sign, t_fractal *fractal)
{
	if (sign == '+')
	{
		fractal->data.im_max += 0.1;
		fractal->data.im_min += 0.1;
	}
	else
	{
		fractal->data.im_max -= 0.1;
		fractal->data.im_min -= 0.1;
	}
}

void	ft_operate_real(char sign, t_fractal *fractal)
{
	if (sign == '+')
	{
		fractal->data.re_min += 0.1;
		fractal->data.re_max += 0.1;
	}
	else
	{
		fractal->data.re_max -= 0.1;
		fractal->data.re_min -= 0.1;
	}
}
