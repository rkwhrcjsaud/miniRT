/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:24:05 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:58:41 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	insert_color(t_data *data, t_color *color, char *line)
{
	char	**rgb;

	if (!line)
		ft_error(data, ERRNO);
	rgb = ft_split(line, ',');
	if (!rgb)
		ft_error(data, ERRNO);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		ft_error(data, E_COLOR);
	color->r = ft_atof(rgb[0]);
	if (color->r == (double)INT_MAX + 1)
		ft_error(data, E_RANGE);
	color->g = ft_atof(rgb[1]);
	if (color->g == (double)INT_MAX + 1)
		ft_error(data, E_RANGE);
	color->b = ft_atof(rgb[2]);
	if (color->b == (double)INT_MAX + 1)
		ft_error(data, E_RANGE);
	if (color->r > COLOR_MAX || color->r < COLOR_MIN
		|| color->g > COLOR_MAX || color->g < COLOR_MIN
		|| color->b > COLOR_MAX || color->b < COLOR_MIN)
		ft_error(data, E_RANGE);
	free_double_arr(rgb);
	set_color_code(color);
}

void	insert_coordinate(t_data *data, t_point *point, char *line)
{
	char	**xyz;

	if (!line)
		ft_error(data, ERRNO);
	xyz = ft_split(line, ',');
	if (!xyz)
		ft_error(data, ERRNO);
	if (xyz[0] && xyz[1] && xyz[2] && !xyz[3])
	{
		point->x = ft_atof(xyz[0]);
		if (point->x == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
		point->y = ft_atof(xyz[1]);
		if (point->y == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
		point->z = ft_atof(xyz[2]);
		if (point->z == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
	}
	else
		ft_error(data, E_ARGUMENT);
	free_double_arr(xyz);
}

static void	check_zero_vector(t_data *data, t_point *vector)
{
	if (!vector->x && !vector->y && !vector->z)
		ft_error(data, E_VECOTR);
	if (vector->x > 1 || vector->x < -1 || vector->y > 1
		|| vector->y < -1 || vector->z > 1 || vector->z < -1)
		ft_error(data, E_RANGE);
}

void	insert_vector(t_data *data, t_point *point, char *line)
{
	char	**xyz;

	if (!line)
		ft_error(data, ERRNO);
	xyz = ft_split(line, ',');
	if (!xyz)
		ft_error(data, ERRNO);
	if (xyz[0] && xyz[1] && xyz[2] && !xyz[3])
	{
		point->x = ft_atof(xyz[0]);
		if (point->x == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
		point->y = ft_atof(xyz[1]);
		if (point->y == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
		point->z = ft_atof(xyz[2]);
		if (point->z == (double)INT_MAX + 1)
			ft_error(data, E_RANGE);
	}
	else
		ft_error(data, E_ARGUMENT);
	check_zero_vector(data, point);
	*point = vunit(*point);
	free_double_arr(xyz);
}
