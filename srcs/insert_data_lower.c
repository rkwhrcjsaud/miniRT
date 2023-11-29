/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:14:10 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/29 14:11:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	insert_plane(t_data *data, char **word)
{
	t_plane	*temp;

	if (!word[1] || !word[2] || !word[3] || word[4])
		argument_error();
	temp = ft_calloc(1, sizeof(t_plane));
	if (!temp)
		errno_error();
	insert_coordinate(data, &temp->point, word[1]);
	insert_vector(data, &temp->vector, word[2]);
	temp->vector = vunit(temp->vector);
	if (!ft_strcmp("checkerboard", word[3]))
		temp->disruption = 1;
	else
	{
		temp->disruption = 0;
		insert_color(data, &temp->color, word[3]);
	}
	ft_lstadd_back(&data->plane, ft_lstnew(temp));
}

void	insert_sphere(t_data *data, char **word)
{
	t_sphere	*temp;

	if (!word[1] || !word[2] || !word[3] || word[4])
		argument_error();
	temp = ft_calloc(1, sizeof(t_sphere));
	if (!temp)
		errno_error();
	insert_coordinate(data, &temp->point, word[1]);
	temp->radius = ft_atof(word[2]) / 2;
	if (temp->radius == (double)INT_MAX + 1)
		out_of_range_error();
	if (!ft_strcmp("checkerboard", word[3]))
		temp->disruption = 1;
	else if (!ft_strcmp("earth", word[3]))
		temp->bump_mapping = 1;
	else
	{
		temp->bump_mapping = 0;
		temp->disruption = 0;
		insert_color(data, &temp->color, word[3]);
	}
	ft_lstadd_back(&data->sphere, ft_lstnew(temp));
}

void	insert_cylinder(t_data *data, char **word)
{
	t_cyl	*temp;

	if (!word[1] || !word[2] || !word[3] || !word[4] || !word[5] || word[6])
		argument_error();
	temp = ft_calloc(1, sizeof(t_cyl));
	if (!temp)
		errno_error();
	insert_coordinate(data, &temp->point, word[1]);
	insert_vector(data, &temp->vector, word[2]);
	temp->vector = vunit(temp->vector);
	temp->radius = ft_atof(word[3]) / 2;
	if (temp->radius == (double)INT_MAX + 1)
		out_of_range_error();
	temp->height = ft_atof(word[4]);
	if (temp->height == (double)INT_MAX + 1)
		out_of_range_error();
	if (!ft_strcmp("checkerboard", word[5]))
		temp->disruption = 1;
	else
	{
		temp->disruption = 0;
		insert_color(data, &temp->color, word[5]);
	}
	ft_lstadd_back(&data->cylinder, ft_lstnew(temp));
}

void	insert_cone(t_data *data, char **word)
{
	t_cone	*temp;

	if (!word[1] || !word[2] || !word[3] || !word[4] || !word[5] || word[6])
		argument_error();
	temp = ft_calloc(1, sizeof(t_cone));
	if (!temp)
		errno_error();
	insert_coordinate(data, &temp->point, word[1]);
	insert_vector(data, &temp->vector, word[2]);
	temp->radius = ft_atof(word[3]);
	if (temp->radius == (double)INT_MAX + 1)
		out_of_range_error();
	temp->height = ft_atof(word[4]);
	if (temp->height == (double)INT_MAX + 1)
		out_of_range_error();
	if (!ft_strcmp("checkerboard", word[5]))
		temp->disruption = 1;
	else
	{
		temp->disruption = 0;
		insert_color(data, &temp->color, word[5]);
	}
	ft_lstadd_back(&data->cone, ft_lstnew(temp));
}
