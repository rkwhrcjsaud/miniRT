/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:21:46 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/24 15:54:04 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vlength(t_point	v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_point	dir_vector(t_point n1, t_point n2)
{
	return (vunit(vminus(n1, n2)));
}

t_point	v_unit_point(t_point p, t_point dest)
{
	t_point	result;

	result.x = p.x * dest.x;
	result.y = p.y * dest.y;
	result.z = p.z * dest.z;
	return (result);
}
