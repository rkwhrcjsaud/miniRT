/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:56:42 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/27 19:49:58 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	shading(t_data *data, t_point ray, t_point inter, t_light *light)
{
	t_ray	light_ray;

	light_ray.hit = init_t_hit();
	light_ray.origin = inter;
	light_ray.dir = ray;
	tracing_plane(data, &light_ray);
	tracing_sphere(data, &light_ray);
	tracing_cylinder(data, &light_ray);
	tracing_cone(data, &light_ray);
	if (light_ray.hit.t == INF
		|| light_ray.hit.t >= vlength(vminus(light->point, inter)) - EPSILON)
		return (0);
	return (1);
}
