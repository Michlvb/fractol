/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printchar.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:25:47 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:25:48 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printchar(int val, int *count)
{
	char	c;

	c = val;
	*count += write(1, &c, 1);
}
