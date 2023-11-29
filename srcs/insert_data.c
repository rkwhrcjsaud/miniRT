/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:56:50 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:48:49 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_identifier(char *id)
{
	if (!id)
		return (-1);
	if (!ft_strcmp(id, WORD_AMBIENT))
		return (FLAG_AMBIENT);
	if (!ft_strcmp(id, WORD_CAMERA))
		return (FLAG_CAMERA);
	if (!ft_strcmp(id, WORD_CYLINDER))
		return (FLAG_CYLINDER);
	if (!ft_strcmp(id, WORD_LIGHT))
		return (FLAG_LIGHT);
	if (!ft_strcmp(id, WORD_PLANE))
		return (FLAG_PLANE);
	if (!ft_strcmp(id, WORD_SPHERE))
		return (FLAG_SPHERE);
	if (!ft_strcmp(id, WORD_CONE))
		return (FLAG_CONE);
	return (-1);
}

int	insert_data(t_data *data, char **word)
{
	static int	upper_flag;
	int			flag;

	flag = check_identifier(word[0]);
	if (flag == FLAG_AMBIENT && !((upper_flag >> FLAG_AMBIENT) & 1))
		insert_ambient(data, word, &upper_flag);
	else if (flag == FLAG_CAMERA && !((upper_flag >> FLAG_CAMERA) & 1))
		insert_camera(data, word, &upper_flag);
	else if (flag == FLAG_LIGHT)
		insert_light(data, word);
	else if (flag == FLAG_PLANE)
		insert_plane(data, word);
	else if (flag == FLAG_SPHERE)
		insert_sphere(data, word);
	else if (flag == FLAG_CYLINDER)
		insert_cylinder(data, word);
	else if (flag == FLAG_CONE)
		insert_cone(data, word);
	else
		ft_error(data, E_TYPE);
	return (upper_flag);
}
