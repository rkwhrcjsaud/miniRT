/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:40:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/24 15:49:51 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tracing_sphere(t_data *data, t_ray *ray)
{
	t_list		*list;
	t_sphere	*sp;
	t_hit		temp_hit;

	list = data->sphere;
	while (list)
	{
		sp = list->content;
		temp_hit = hit_sphere(sp, *ray);
		if (temp_hit.t > EPSILON && temp_hit.t < INF && temp_hit.t < ray->hit.t)
		{
			ray->hit = temp_hit;
			ray->hit.c = sp->color;
			ray->hit.disruption = sp->disruption;
			ray->hit.obj_num = FLAG_SPHERE;
			ray->hit.object = (void *)sp;
		}
		list = list->next;
	}
}

t_hit	hit_sphere_nv(t_sphere *s, t_ray ray, double t)
{
	t_point	nv;
	t_point	inter;

	inter = vsum(ray.origin, vmul(ray.dir, t));
	nv = vunit(vminus(inter, s->point));
	if (vdot(ray.dir, nv) > 0)
		return (tie_hit(t, vmul(nv, -1)));
	return (tie_hit(t, nv));
}

t_hit	hit_sphere(t_sphere *s, t_ray ray)
{
	double	b;
	double	c;
	double	temp;

	b = vdot(ray.dir, vminus(ray.origin, s->point));
	c = vdot(vminus(s->point, ray.origin), vminus(s->point, ray.origin))
		- s->radius * s->radius;
	temp = b * b - c;
	if (temp < 0)
		return (tie_hit(0, tie_vector(0, 0, 0)));
	temp = sqrt(temp);
	if (-b - temp > 0)
		return (hit_sphere_nv(s, ray, -b - temp));
	if (-b + temp > 0)
		return (hit_sphere_nv(s, ray, -b + temp));
	return (tie_hit(0, tie_vector(0, 0, 0)));
}
