/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:26:27 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:26:28 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_printstr("-2147483648", count);
			return ;
		}		
		else
		{
			ft_printchar('-', count);
			n *= -1;
		}
	}
	if (n >= 10)
	{
		ft_putnbr((n / 10), count);
		ft_putnbr((n % 10), count);
	}
	else if (n < 10)
	{
		ft_printchar((n + '0'), count);
	}
}
