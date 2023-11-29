/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:34:37 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/15 15:36:11 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	iscolor(t_color a)
{
	return (!(a.r < COLOR_MIN || a.r > COLOR_MAX
			|| a.g < COLOR_MIN || a.g > COLOR_MAX
			|| a.b < COLOR_MIN || a.b > COLOR_MAX));
}

int	isvector(t_point a)
{
	return (!(a.x < -1.0 || a.x > 1.0
			|| a.y < -1.0 || a.y > 1.0
			|| a.z < -1.0 || a.z > 1.0));
}

int	isratio(double a)
{
	return (!(a < 0 || a > 1));
}

int	isfov(int a)
{
	return (!(a < 0 || a > 180));
}

void	free_double_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}
