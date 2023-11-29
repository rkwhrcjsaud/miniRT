/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:42:51 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/27 19:55:33 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tracing_cylinder(t_data *data, t_ray *ray)
{
	t_list	*list;
	t_cyl	*cy;
	t_hit	temp_hit;

	list = data->cylinder;
	while (list)
	{
		cy = list->content;
		temp_hit = hit_cylinder(cy, *ray);
		if (temp_hit.t > EPSILON && temp_hit.t < INF && temp_hit.t < ray->hit.t)
		{
			ray->hit = temp_hit;
			ray->hit.c = cy->color;
			ray->hit.disruption = cy->disruption;
			ray->hit.obj_num = FLAG_CYLINDER;
			ray->hit.object = (void *)cy;
		}
		list = list->next;
	}
}

double	hit_cylinder_inf(t_cyl *cy, t_ray ray)
{
	t_point	w;
	double	a;
	double	b;
	double	c;
	double	temp;

	w = vminus(ray.origin,
			vminus(cy->point, vdiv(vmul(cy->vector, cy->height), 2)));
	a = vdot(ray.dir, ray.dir)
		- pow(vdot(ray.dir, vunit(vmul(cy->vector, cy->height))), 2);
	b = 2 * (vdot(ray.dir, w)
			- vdot(ray.dir, vunit(vmul(cy->vector, cy->height)))
			* vdot(w, vunit(vmul(cy->vector, cy->height))));
	c = vdot(w, w) - pow(vdot(w, vunit(vmul(cy->vector, cy->height))), 2)
		- pow(cy->radius, 2);
	if (b * b - 4 * a * c < 0)
		return (-1);
	temp = sqrt(b * b - 4 * a * c);
	if ((-b - temp) / (2 * a) > 0)
		return ((-b - temp) / (2 * a));
	if ((-b + temp) / (2 * a) > 0)
		return ((-b + temp) / (2 * a));
	return (-1);
}

double	hit_cylinder_lid(t_cyl *cy, t_ray ray, double lc)
{
	t_point	tc;
	t_point	th;
	double	t;
	double	temp;

	temp = vdot(vmul(cy->vector, cy->height), vmul(cy->vector, cy->height));
	if (lc < 0 && vdot(cy->vector, ray.dir))
	{
		tc = vminus(cy->point, vmul(cy->vector, cy->height / 2));
		t = (vdot(cy->vector, tc) - vdot(cy->vector, ray.origin))
			/ vdot(cy->vector, ray.dir);
		if (pow(vlength(vminus(vsum(ray.origin, vmul(ray.dir, t)), tc)), 2)
			<= pow(cy->radius, 2))
			return (t);
	}
	if (lc > temp && vdot(cy->vector, ray.dir))
	{
		th = vsum(cy->point, vmul(cy->vector, cy->height / 2));
		t = (vdot(cy->vector, th) - vdot(cy->vector, ray.origin))
			/ vdot(cy->vector, ray.dir);
		if (pow(vlength(vminus(vsum(ray.origin, vmul(ray.dir, t)), th)), 2)
			<= pow(cy->radius, 2))
			return (t);
	}
	return (0);
}

t_hit	hit_cylinder_side_nv(t_cyl *cy, t_ray ray, double t)
{
	t_point	nv;
	t_point	inter;

	inter = vsum(ray.origin, vmul(ray.dir, t));
	nv = vminus(inter, cy->point);
	nv = vminus(nv, vmul(cy->vector, vdot(nv, cy->vector)));
	nv = vunit(nv);
	if (vdot(nv, ray.dir) > 0)
		return (tie_hit(t, vminus(nv, vmul(nv, 2))));
	return (tie_hit(t, nv));
}

t_hit	hit_cylinder(t_cyl *cy, t_ray ray)
{
	t_point	h;
	double	t;
	double	lc;

	h = vmul(cy->vector, cy->height);
	t = hit_cylinder_inf(cy, ray);
	if (t == -1)
		return (tie_hit(0, tie_vector(0, 0, 0)));
	lc = vdot(vminus(vsum(ray.origin, vmul(ray.dir, t)),
				vminus(cy->point, vdiv(h, 2))), h);
	if (lc >= 0 && lc <= vdot(h, h))
		return (hit_cylinder_side_nv(cy, ray, t));
	if (vdot(ray.dir, cy->vector) > 0)
		return (tie_hit(hit_cylinder_lid(cy, ray, lc),
				vminus(cy->vector, vmul(cy->vector, 2))));
	return (tie_hit(hit_cylinder_lid(cy, ray, lc), cy->vector));
}
