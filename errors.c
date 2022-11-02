/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:28:37 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 10:30:53 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	program_usage(void)
{
	ft_printf("%s", "\nIncorrect input!\n");
	ft_printf("%s", "The following fractal sets are available:\n");
	ft_printf("%s", "- Julia\n");
	ft_printf("%s", "- Mandelbrot\n");
	ft_printf("%s", "The program is called in the following formats:\n");
	ft_printf("%s", "./fractal.a mandelbrot\n");
	ft_printf("%s", "./fractal.a julia <double> <double> \n\n");
	exit(1);
}
