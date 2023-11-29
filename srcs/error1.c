/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:53 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/28 18:01:25 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(t_data *data, int e_flag)
{
	ft_close(data->fd);
	if (e_flag == ERRNO)
		errno_error();
	else if (e_flag == E_TYPE)
		insert_data_error();
	else if (e_flag == E_ARGUMENT)
		argument_error();
	else if (e_flag == E_MLX)
		mlx_error();
	else if (e_flag == E_RANGE)
		out_of_range_error();
	else if (e_flag == E_VECOTR)
		vector_error();
	else if (e_flag == E_COLOR)
		color_error();
}

void	insert_data_error(void)
{
	write(2, "Error\nType identifier is wrong or duplicated!\n", 46);
	exit(1);
}

void	argument_error(void)
{
	write(2, "Error\nNubmer of argument is worng!\n", 35);
	exit(1);
}

void	mlx_error(void)
{
	write(2, "Error\nMlx function has malfunctioned!\n", 38);
	exit(1);
}

void	out_of_range_error(void)
{
	write(2, "Error\nValue is out of range!\n", 29);
	exit(1);
}
