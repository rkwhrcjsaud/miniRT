/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:17:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/29 14:16:17 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	light_effect(t_data *data, t_light *light, t_ray ray)
{
	t_color	c1;
	t_color	c2;

	c1 = lambert(light, ray);
	c2 = ambient(data);
	return (color_sum(c1, c2));
}

t_color	lambert(t_light *light, t_ray ray)
{
	t_point	l;
	t_color	result;
	double	angle;
	double	ratio;
	double	brightness;

	l = vunit(vminus(light->point, ray.inter));
	angle = vdot(ray.hit.nv, l);
	if (angle < 0)
		angle = 0;
	ratio = light->ratio;
	brightness = angle * ratio * (1.0 / (1.0 + (ATTENUATION
					* pow(vlength(vminus(light->point, ray.inter)), 2))));
	result.r = light->color.r * brightness;
	if (result.r < 0)
		result.r = 0;
	result.g = light->color.g * brightness;
	if (result.g < 0)
		result.g = 0;
	result.b = light->color.b * brightness;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

t_color	blinn_phong(t_light *light, t_ray ray)
{
	t_point	l;
	double	angle;
	t_point	half_v;
	t_color	result;
	double	brightness;

	l = vunit(vminus(light->point, ray.inter));
	half_v = vunit(vminus(l, ray.dir));
	angle = vdot(ray.hit.nv, half_v);
	angle = pow(angle, SPECULAR);
	brightness = angle * light->ratio * (1.0 / (1.0 + (ATTENUATION
					* pow(vlength(vminus(light->point, ray.inter)), 2))));
	result.r = light->color.r * brightness;
	if (result.r < 0)
		result.r = 0;
	result.g = light->color.g * brightness;
	if (result.g < 0)
		result.g = 0;
	result.b = light->color.b * brightness;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

t_color	ambient(t_data *data)
{
	t_color	result;

	result.r = data->amb.color.r * data->amb.ratio;
	result.g = data->amb.color.g * data->amb.ratio;
	result.b = data->amb.color.b * data->amb.ratio;
	return (result);
}
