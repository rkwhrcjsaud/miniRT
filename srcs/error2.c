/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:00:45 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:42:43 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vector_error(void)
{
	write(2, "Error\nzero vector is not allowed!\n", 34);
	exit(1);
}

void	color_error(void)
{
	write(2, "Error\nColor value is worng!\n", 28);
	exit(1);
}

void	errno_error(void)
{
	char	*error_string;

	error_string = strerror(errno);
	write(2, "Error\n", 6);
	write(2, error_string, ft_strlen(error_string));
	exit(1);
}
