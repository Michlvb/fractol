/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 16:16:26 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 11:48:40 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

char	*ft_tolower(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
		{
			str[i] += 32;
		}
		i++;
	}
	return (str);
}

static void	get_res(char *str, double *res)
{
	int		len;

	len = 0;
	while (ft_isdigit(*str))
	{
		*res = ((*res * 10) + (*str) - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			*res = ((*res * 10) + (*str) - '0');
			str++;
			len++;
		}
	}
	while (len--)
		*res /= 10;
}

double	ft_atof(char *str)
{
	double	res;
	int		sign;

	res = 0;
	sign = 1;
	if (!str)
		return (0.0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	get_res(str, &res);
	return (res * sign);
}

void	parse_input(t_fractal *fractal, char *argv[])
{
	char	*frac;

	frac = ft_tolower(argv[1]);
	if (ft_strcmp(frac, "mandelbrot") == 0)
	{
		fractal->julia = 0;
		return ;
	}
	else if (ft_strcmp(frac, "julia") == 0)
	{
		if (argv[2] == NULL || argv[3] == NULL)
			program_usage();
		fractal->julia = 1;
		return ;
	}
	program_usage();
}
