/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:02 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/22 18:24:56 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > data->win.x || y > data->win.y)
		return ;
	dst = data->mlx.img.addr + (y * data->mlx.img.line_length
			+ x * (data->mlx.img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
