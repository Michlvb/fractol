/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fractal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 18:20:48 by mlammert      #+#    #+#                 */
/*   Updated: 2022/02/17 21:09:43 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ErrorMessage(void)
{
	printf("Incorrect input\n");
	printf("The following inputs are valid:\n");
	printf("- Julia or julia <float> <float>\n");
	printf("- Mandelbrot or mandelbrot\n");
    exit(0);
	return (0);
}

int ft_isAlpha(char c)
{
    if ((c < '0' || c > '9') && c != '.' \
        && c != '-' && c != '+')
        return (1);
    return (0);
}

double  ft_convert(char *str)
{
    int i;
    int count;
    double  result;

    result = 0;
    count = 1.0;
    i = 0;
    // printf("CHeck string: %s\n", str);
    while (*str)
    {
        if (ft_isAlpha(*str))
            return (ErrorMessage());
        if (*str == '.')
        {
            str++;
            while (*str)
            {
                if (ft_isAlpha(*str))
                    return (ErrorMessage());
                result = (result * 10.0) + (*str - '0');
                count *= 10.0;
                str++;
            }
        }
        else
        {
            result = (result * 10.0) + (*str - '0');
            str++;
        }
    }
    return ((result / count));
}

double  ft_atof(char *str)
{
    double negate;
    int count;
    double result;

    count = 0;
    negate = 1.0;
    if (ft_isAlpha(*str))
        return (ErrorMessage());
    while (*str == '-' || *str == '+')
    {
        if (*str == '-')
            negate *= -1;
        str++;
    }
    result = ft_convert(str);
    return (result * negate);
}

int	check_args(int argc, char *argv[], t_vars *vars)
{
	if (argc < 2)
		return (ErrorMessage());
    else if (ft_strcmp(argv[1], "mandelbrot") == 0 || \
			ft_strcmp(argv[1], "Mandelbrot") == 0)
		vars->julia = 0;
	else if (ft_strcmp(argv[1], "julia") == 0 || \
			ft_strcmp(argv[1], "Julia") == 0)
		{
            vars->julia = 1;
            if (!argv[2] || !argv[3])
                return (ErrorMessage());
            vars->data.save_re = ft_atof(argv[2]);
            vars->data.save_im = ft_atof(argv[3]);
        }
	else
		return (ErrorMessage());
    return (1);
}