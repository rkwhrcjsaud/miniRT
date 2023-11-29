/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:13:18 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 16:31:29 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	tie_vector(double a, double b, double c)
{
	t_point	temp;

	temp.x = a;
	temp.y = b;
	temp.z = c;
	return (temp);
}

t_point	vcross(t_point a, t_point b)
{
	t_point	temp;

	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return (temp);
}

t_point	vsum(t_point a, t_point b)
{
	t_point	temp;

	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	return (temp);
}

t_point	vminus(t_point a, t_point b)
{
	t_point	temp;

	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	return (temp);
}

t_point	vmul(t_point a, double s)
{
	t_point	temp;

	temp.x = a.x * s;
	temp.y = a.y * s;
	temp.z = a.z * s;
	return (temp);
}
