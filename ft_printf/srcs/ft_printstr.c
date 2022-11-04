/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printstr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:26:21 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 18:26:22 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
		*count += write(1, "(null)", 6);
	else
		while (str[i])
			*count += write(1, &(str[i++]), 1);
}
