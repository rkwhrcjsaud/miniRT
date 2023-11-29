/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:59:15 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/27 17:19:16 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_tracing(t_data *data)
{
	int		i;
	int		j;
	t_ray	ray;
	t_color	color;

	calc_camera_vector(&data->cam);
	i = 0;
	while (i <= data->win.y)
	{
		j = 0;
		while (j <= data->win.x)
		{
			ray.origin = data->cam.point;
			ray.dir = calc_ray_direction(data, j, i);
			color = objects_tracing(data, &ray, 0);
			set_color_code(&color);
			my_mlx_pixel_put(data, j, i, color.code);
			j++;
		}
		i++;
	}
}

t_color	objects_tracing(t_data *data, t_ray *ray, int depth)
{
	t_color	color;

	ray->hit = init_t_hit();
	tracing_plane(data, ray);
	tracing_sphere(data, ray);
	tracing_cylinder(data, ray);
	tracing_cone(data, ray);
	if (ray->hit.t == INF || ray->hit.t == 0)
		return (tie_color(0, 0, 0));
	ray->inter = vsum(vsum(ray->origin,
				vmul(ray->dir, ray->hit.t)), vmul(ray->hit.nv, EPSILON));
	if (ray->hit.disruption)
		object_disruption(ray);
	if (ray->hit.obj_num == FLAG_SPHERE)
		bump_mapping(data, ray->hit.object, ray);
	light_tracing(data, ray);
	color = ray->hit.c;
	ray->origin = ray->inter;
	ray->dir = vunit(vsum(ray->dir, vmul(ray->hit.nv,
					2 * vdot(vmul(ray->dir, -1), ray->hit.nv))));
	if (depth == REFLECT_MAX)
		return (color);
	return (color_sum(color_mul(color, 1 - REFLECT),
			color_mul(objects_tracing(data, ray, depth + 1), REFLECT)));
}

void	light_tracing(t_data *data, t_ray *ray)
{
	t_list	*list;
	t_light	*l;
	t_color	temp;

	list = data->light;
	temp = ambient(data);
	while (list)
	{
		l = list->content;
		if (!shading(data, dir_vector(l->point, ray->inter), ray->inter, l))
			temp = color_sum(lambert(l, *ray), temp);
		list = list->next;
	}
	temp = surface_reflect(temp, ray->hit);
	list = data->light;
	while (list)
	{
		l = list->content;
		if (!shading(data, dir_vector(l->point, ray->inter), ray->inter, l))
			temp = color_sum(blinn_phong(l, *ray), temp);
		list = list->next;
	}
	ray->hit.c = temp;
	set_color_code(&ray->hit.c);
}

t_hit	tie_hit(double t, t_point p)
{
	t_hit	temp;

	temp.t = t;
	temp.nv = p;
	return (temp);
}

t_hit	init_t_hit(void)
{
	t_hit	temp_hit;

	temp_hit = tie_hit(INF, tie_vector(0, 0, 0));
	temp_hit.obj_num = 0;
	temp_hit.object = NULL;
	temp_hit.disruption = 0;
	temp_hit.c.r = 0;
	temp_hit.c.g = 0;
	temp_hit.c.b = 0;
	temp_hit.c.code = 0;
	return (temp_hit);
}
