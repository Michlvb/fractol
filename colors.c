/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 19:47:33 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/22 10:08:06 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_palette(int range)
{
	int	colors[16];

	colors[0] = 0x000000;
	colors[1] = 0x19071a;
	colors[2] = 0x09012f;
	colors[3] = 0x040449;
	colors[4] = 0x000764;
	colors[5] = 0x0c2c8a;
	colors[6] = 0x1852b1;
	colors[7] = 0x397dd1;
	colors[8] = 0x86b5e5;
	colors[9] = 0xd3ecf8;
	colors[10] = 0xf1e9bf;
	colors[11] = 0xf8c95f;
	colors[12] = 0xffaa00;
	colors[13] = 0xcc8000;
	colors[14] = 0x995700;
	colors[15] = 0x6a3403;
	return (colors[range % 16]);
}
