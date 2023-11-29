/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:21:14 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/21 19:54:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tracing_plane(t_data *data, t_ray *ray)
{
	t_list	*list;
	t_plane	*pl;
	t_hit	temp_hit;

	list = data->plane;
	while (list)
	{
		pl = list->content;
		temp_hit = hit_plane(pl, *ray);
		if (temp_hit.t > EPSILON && temp_hit.t < INF && temp_hit.t < ray->hit.t)
		{
			ray->hit = temp_hit;
			ray->hit.c = pl->color;
			ray->hit.disruption = pl->disruption;
			ray->hit.obj_num = FLAG_PLANE;
			ray->hit.object = (void *)pl;
		}
		list = list->next;
	}
}

t_hit	hit_plane(t_plane *p, t_ray ray)
{
	double	t;

	if (vdot(p->vector, ray.dir) == 0)
		return (tie_hit(0, tie_vector(0, 0, 0)));
	t = (vdot(p->vector, p->point) - vdot(p->vector, ray.origin))
		/ vdot(p->vector, ray.dir);
	if (t > 0)
	{
		if (vdot(ray.dir, p->vector) > 0)
			return (tie_hit(t, vminus(p->vector, vmul(p->vector, 2))));
		return (tie_hit(t, p->vector));
	}
	return (tie_hit(0, tie_vector(0, 0, 0)));
}
