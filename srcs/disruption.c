/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:26:14 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/27 17:33:12 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_disruption(t_ray *ray)
{
	int	black;

	black = 0;
	if (ray->hit.obj_num == FLAG_PLANE)
		black = uv_plane_mapping(ray->hit.object, ray);
	else if (ray->hit.obj_num == FLAG_SPHERE)
		black = uv_sphere_mapping(ray->hit.object, ray);
	else if (ray->hit.obj_num == FLAG_CYLINDER)
		black = uv_cylinder_mapping(ray->hit.object, ray);
	else if (ray->hit.obj_num == FLAG_CONE)
		black = uv_cone_mapping(ray->hit.object, ray);
	if (!black)
		ray->hit.c = tie_color(255, 255, 255);
	else
		ray->hit.c = tie_color(0, 0, 0);
}

int	uv_plane_mapping(t_plane *pl, t_ray *ray)
{
	t_point		vector_x;
	t_point		vector_y;
	double		x;
	double		y;

	vector_x = vcross(pl->vector, tie_vector(1, 0, 0));
	if (vlength(vector_x) == 0)
		vector_x = vcross(pl->vector, tie_vector(0, 1, 0));
	vector_y = vcross(vector_x, pl->vector);
	x = vdot(vector_x, vminus(pl->point, ray->inter));
	y = vdot(vector_y, vminus(pl->point, ray->inter));
	x /= CHEKCKER_PL;
	y /= CHEKCKER_PL;
	if (((int)x + (int)y + (x < 0) + (y < 0)) % 2 == 0)
		return (0);
	else
		return (1);
}
