/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:30:36 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/29 15:05:42 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_mapping(t_data *data, t_sphere *sp, t_ray *ray)
{
	double	phi;
	double	theta;
	double	mapx;
	double	mapy;
	t_point	cp;

	if (sp->bump_mapping)
	{
		cp = vminus(ray->inter, sp->point);
		phi = (asin(cp.z / sp->radius) * 180 / M_PI) + 90;
		theta = (atan2(cp.y, cp.x) * 180 / M_PI) + 180;
		mapy = phi * ((double)data->mlx.img_bump.height / 180);
		mapx = theta * ((double)data->mlx.img_bump.width / 360);
		earth_bump_nv(data, bump_color(data, mapx, mapy), ray);
		mapy = phi * ((double)data->mlx.img_earth.height / 180);
		mapx = theta * ((double)data->mlx.img_earth.width / 360);
		sp->color = earth_color(data, mapx, mapy);
	}
}

int	uv_sphere_mapping(t_sphere *sp, t_ray *ray)
{
	double		x;
	double		y;
	double		z;
	t_point		cp;
	double		theta;

	cp = vminus(ray->inter, sp->point);
	x = vdot(cp, tie_vector(1, 0, 0));
	y = vdot(cp, tie_vector(0, 1, 0));
	z = vdot(cp, tie_vector(0, 0, 1));
	theta = atan(x / y) * 180 / M_PI;
	if (x < 0 ^ y < 0)
		theta += (theta >= 0) * CHEKCKER_R - (theta < 0) * CHEKCKER_R;
	theta /= CHEKCKER_R;
	if (((int)theta % 2 ^ (int)(acos(z / sp->radius) * 180
			/ M_PI / CHEKCKER_R)) % 2)
		return (0);
	else
		return (1);
}

int	uv_cylinder_mapping(t_cyl *cy, t_ray *ray)
{
	double		x;
	double		y;
	double		z;
	double		theta;
	t_point		vector_x;

	vector_x = vcross(cy->vector, tie_vector(0, 1, 0));
	if (vlength(vector_x) == 0)
		vector_x = vcross(cy->vector, tie_vector(1, 0, 0));
	x = vdot(vector_x, vminus(ray->inter, cy->point));
	y = vdot(vcross(cy->vector, vector_x), vminus(ray->inter, cy->point));
	z = vdot(vminus(ray->inter, cy->point), cy->vector);
	theta = atan(x / y) * 180 / M_PI;
	if (x < 0 ^ y < 0)
		theta += (theta >= 0) * CHEKCKER_R - (theta < 0) * CHEKCKER_R;
	theta /= CHEKCKER_R;
	if (vdot(cy->vector, ray->hit.nv) > 1 - EPSILON
		|| vdot(cy->vector, ray->hit.nv) < -1 + EPSILON)
		return (((int)(x / CHEKCKER_CY)
			+ (int)(y / CHEKCKER_CY) + (x < 0) + (y < 0)) % 2);
	if ((((int)theta + (int)(z / CHEKCKER_Z)) + (z < 0)) % 2 == 0)
		return (0);
	else
		return (1);
}

int	uv_cone_mapping(t_cone *cn, t_ray *ray)
{
	t_point	vector_x;
	double	x;
	double	y;
	double	z;

	vector_x = vcross(cn->vector, tie_vector(0, 1, 0));
	if (vlength(vector_x) == 0)
		vector_x = vcross(cn->vector, tie_vector(1, 0, 0));
	x = vdot(vector_x, vminus(ray->inter, cn->point));
	y = vdot(vcross(cn->vector, vector_x), vminus(ray->inter, cn->point));
	if (x == 0)
		z = 0;
	else
		z = atan(y / x) * 180 / M_PI;
	if (x <= 0 ^ y <= 0)
		z += (z >= 0) * CHEKCKER_R - (z < 0) * CHEKCKER_R;
	z /= CHEKCKER_R;
	if (vdot(cn->vector, ray->hit.nv) > 1 - EPSILON
		|| vdot(cn->vector, ray->hit.nv) < -1 + EPSILON)
		return (((int)(x / CHEKCKER_CN)
			+ (int)(y / CHEKCKER_CN) + (x < 0) + (y < 0)) % 2);
	return (((int)z + (int)(vdot(cn->vector, vminus(ray->inter, cn->point))
			/ CHEKCKER_Z)) % 2);
}
