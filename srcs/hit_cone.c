/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:40:09 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/21 20:18:04 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tracing_cone(t_data *data, t_ray *ray)
{
	t_list		*list;
	t_cone		*cn;
	t_hit		temp_hit;

	list = data->cone;
	while (list)
	{
		cn = list->content;
		temp_hit = hit_cone(cn, *ray);
		if (temp_hit.t > EPSILON && temp_hit.t < INF && temp_hit.t < ray->hit.t)
		{
			ray->hit = temp_hit;
			ray->hit.c = cn->color;
			ray->hit.disruption = cn->disruption;
			ray->hit.obj_num = FLAG_CONE;
			ray->hit.object = (void *)cn;
		}
		list = list->next;
	}
}

t_hit	hit_cone_lid(t_cone *cn, t_ray ray)
{
	double	t;

	if (vdot(cn->vector, ray.dir))
	{
		t = (vdot(cn->vector, vsum(cn->point, vmul(cn->vector, cn->height)))
				- vdot(cn->vector, ray.origin))
			/ vdot(cn->vector, ray.dir);
		if (t > EPSILON && vlength(vminus(vsum(ray.origin,
						vmul(ray.dir, t)), vsum(cn->point,
						vmul(cn->vector, cn->height)))) <= cn->radius)
		{
			if (vdot(cn->vector, ray.dir) > 0)
				return (tie_hit(t, vmul(cn->vector, -1)));
			return (tie_hit(t, cn->vector));
		}
	}
	return (tie_hit(0, tie_vector(0, 0, 0)));
}

t_hit	hit_cone_nv(t_cone *cn, t_ray ray, double t)
{
	t_point	nv;
	t_point	cp;
	t_point	inter;

	inter = vsum(ray.origin, vmul(ray.dir, t));
	cp = vminus(inter, cn->point);
	if (vdot(cp, cn->vector) > cn->height
		|| vdot(cp, cn->vector) < 0)
		return (hit_cone_lid(cn, ray));
	nv = vunit(vminus(cp,
				vmul(cn->vector, pow(vlength(cp), 2) / vdot(cp, cn->vector))));
	if (vdot(ray.dir, nv) > 0)
		return (tie_hit(t, vmul(nv, -1)));
	return (tie_hit(t, nv));
}

t_hit	hit_cone_check(t_cone *cn, t_ray ray, double t1, double t2)
{
	t_hit	hit1;
	t_hit	hit2;

	hit1 = hit_cone_nv(cn, ray, t1);
	hit2 = hit_cone_nv(cn, ray, t2);
	if (hit1.t < hit2.t && hit1.t > 0)
		return (hit1);
	else if (hit2.t > 0)
		return (hit2);
	return (tie_hit(0, tie_vector(0, 0, 0)));
}

t_hit	hit_cone(t_cone *cn, t_ray ray)
{
	t_point	w;
	double	a;
	double	b;
	double	c;
	double	temp;

	w = vminus(ray.origin, cn->point);
	a = vdot(ray.dir, ray.dir)
		- (pow(cn->radius / cn->height, 2) + 1)
		* pow(vdot(ray.dir, cn->vector), 2);
	b = 2 * (vdot(ray.dir, w)
			- (pow(cn->radius / cn->height, 2) + 1) * vdot(ray.dir,
				cn->vector) * vdot(w, cn->vector));
	c = vdot(w, w) - (pow(cn->radius / cn->height, 2) + 1)
		* pow(vdot(w, cn->vector), 2);
	temp = b * b - 4 * a * c;
	if (temp < 0)
		return (tie_hit(0, tie_vector(0, 0, 0)));
	temp = sqrt(temp);
	return (hit_cone_check(cn, ray,
			(-b - temp) / (2 * a), (-b + temp) / (2 * a)));
}
