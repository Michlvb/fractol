/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printhex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:26:04 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:26:06 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printhex(t_u64 n, char *str, int *count)
{
	if (n > 15)
	{
		ft_printhex((n / 16), str, count);
		ft_printhex((n % 16), str, count);
	}
	else
	{
		ft_printchar(str[n], count);
	}
}

void	ft_prephex(t_u64 n, char c, int *count)
{
	if (c == 'x')
		ft_printhex(n, "0123456789abcdef", count);
	else if (c == 'X')
		ft_printhex(n, "0123456789ABCDEF", count);
}
