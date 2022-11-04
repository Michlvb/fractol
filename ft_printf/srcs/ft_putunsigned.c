/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putunsigned.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:26:35 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:26:37 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putunsigned(unsigned int n, int *count)
{
	if (n >= 10)
	{
		ft_putunsigned((n / 10), count);
		ft_putunsigned((n % 10), count);
	}
	else if (n < 10)
	{
		ft_printchar((n + '0'), count);
	}
}
