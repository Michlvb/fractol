/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 18:25:32 by mlammert      #+#    #+#                 */
/*   Updated: 2022/08/11 19:00:14 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef unsigned long long	t_u64;

void	ft_printchar(int c, int *count);
void	ft_printstr(char *str, int *count);
void	ft_putnbr(int nbr, int *count);
void	ft_prephex(t_u64 n, char c, int *count);
void	ft_putunsigned(unsigned int n, int *count);
void	ft_printpointer(void *ptr, int *count);
void	ft_printhex(t_u64 n, char *str, int *count);
int		ft_printf(const char *n_args, ...);

#endif
