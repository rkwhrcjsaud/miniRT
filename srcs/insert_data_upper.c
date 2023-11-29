/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:12:22 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/29 14:08:56 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	insert_ambient(t_data *data, char **word, int *flag)
{
	*flag |= 1 << FLAG_AMBIENT;
	if (!word[1] || !word[2] || word[3])
		ft_error(data, E_ARGUMENT);
	data->amb.ratio = ft_atof(word[1]);
	if (data->amb.ratio < 0 || data->amb.ratio > 1)
		ft_error(data, E_RANGE);
	insert_color(data, &data->amb.color, word[2]);
}

void	insert_camera(t_data *data, char **word, int *flag)
{
	*flag |= 1 << FLAG_CAMERA;
	if (!word[1] || !word[2] || !word[3] || word[4])
		ft_error(data, E_ARGUMENT);
	insert_coordinate(data, &data->cam.point, word[1]);
	insert_vector(data, &data->cam.vector, word[2]);
	data->cam.vector = vunit(data->cam.vector);
	data->cam.fov = ft_atoi(word[3]);
	if (data->cam.fov < 0 || data->cam.fov > 180)
		ft_error(data, E_RANGE);
}

void	insert_light(t_data *data, char **word)
{
	t_light	*temp;

	temp = ft_calloc(1, sizeof(t_light));
	if (!temp)
		ft_error(data, ERRNO);
	if (!word[1] || !word[2] || !word[3] || word[4])
		ft_error(data, E_ARGUMENT);
	insert_coordinate(data, &temp->point, word[1]);
	temp->ratio = ft_atof(word[2]);
	if (temp->ratio > 1 || temp->ratio < 0)
		ft_error(data, E_RANGE);
	insert_color(data, &temp->color, word[3]);
	ft_lstadd_back(&data->light, ft_lstnew(temp));
}
