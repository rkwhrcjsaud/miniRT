/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:41:33 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/28 17:54:20 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		argument_error();
	data_init(&data);
	data_passing(&data, av[1]);
	let_mlx(&data);
	exit(0);
}
