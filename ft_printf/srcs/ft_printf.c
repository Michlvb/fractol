/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:25:57 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 19:31:38 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	parse_type(va_list va_args, const char *args, int *count)
{
	if (*args == 'c')
		ft_printchar(va_arg(va_args, int), count);
	else if (*args == 's')
		ft_printstr(va_arg(va_args, char *), count);
	else if (*args == 'i' || *args == 'd')
		ft_putnbr(va_arg(va_args, int), count);
	else if (*args == 'x' || *args == 'X')
		ft_prephex(va_arg(va_args, unsigned int), *args, count);
	else if (*args == 'u')
		ft_putunsigned(va_arg(va_args, unsigned int), count);
	else if (*args == 'p')
		ft_printpointer(va_arg(va_args, void *), count);
	else if (*args == '%')
		*count += write(1, &(*args), 1);
	else
		return ;
}

int	read_values(va_list va_args, const char *args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == '%')
		{
			i++;
			parse_type(va_args, (args + i), &count);
		}
		else
			ft_printchar(args[i], &count);
		i++;
	}
	return (count);
}

int	ft_printf(const char *n_args, ...)
{
	va_list	args;
	int		n;

	if (!n_args)
		return (1);
	n = 0;
	va_start(args, n_args);
	n = read_values(args, n_args);
	va_end(args);
	return (n);
}
