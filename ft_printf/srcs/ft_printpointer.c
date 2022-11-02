/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printpointer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:26:14 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:26:15 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printpointer(void *ptr, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	*count += write(1, "0x", 2);
	ft_printhex((t_u64)ptr, base, count);
}
