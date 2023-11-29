/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:23:14 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/24 17:41:04 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	vdiv(t_point a, double s)
{
	t_point	temp;

	temp.x = a.x / s;
	temp.y = a.y / s;
	temp.z = a.z / s;
	return (temp);
}

t_point	vunit(t_point a)
{
	if (vlength(a) == 0)
		return (tie_vector(0, 0, 0));
	return (vdiv(a, vlength(a)));
}

double	vdot(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	calc_camera_vector(t_camera *cam)
{
	cam->vector_x = vcross(cam->vector, tie_vector(0, -1, 0));
	if (vlength(cam->vector_x) == 0)
		cam->vector_x = vcross(cam->vector, tie_vector(-1, 0, 0));
	cam->vector_y = vcross(cam->vector_x, cam->vector);
}

t_point	calc_ray_direction(t_data *data, int x, int y)
{
	double	d;
	t_point	u;
	t_point	v;
	t_point	value;

	d = (data->win.x / 2) / tan((data->cam.fov * acos(-1) / 360));
	u = vmul(data->cam.vector_x, (-data->win.x / 2) + (x + 0.5));
	v = vmul(data->cam.vector_y, (-data->win.y / 2) + (y + 0.5));
	value = vunit(vsum(vsum(u, v), vmul(data->cam.vector, d)));
	return (value);
}
