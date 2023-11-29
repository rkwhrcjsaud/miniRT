/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_effect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:12:15 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/21 17:29:34 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_mul(t_color a, double b)
{
	a.r *= b;
	a.g *= b;
	a.b *= b;
	return (a);
}

t_color	tie_color(int a, int b, int c)
{
	t_color	color;

	color.r = a;
	color.g = b;
	color.b = c;
	color.code = 0;
	return (color);
}

void	set_color_code(t_color *a)
{
	if (a->r > COLOR_MAX)
		a->r = COLOR_MAX;
	if (a->g > COLOR_MAX)
		a->g = COLOR_MAX;
	if (a->b > COLOR_MAX)
		a->b = COLOR_MAX;
	a->code = ((int)a->r << 16) + ((int)a->g << 8) + (int)a->b;
}

t_color	color_sum(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	set_color_code(&result);
	return (result);
}

t_color	surface_reflect(t_color light, t_hit temp_hit)
{
	t_color	result;

	result.r = light.r * (double) temp_hit.c.r / COLOR_MAX;
	result.g = light.g * (double) temp_hit.c.g / COLOR_MAX;
	result.b = light.b * (double) temp_hit.c.b / COLOR_MAX;
	return (result);
}
