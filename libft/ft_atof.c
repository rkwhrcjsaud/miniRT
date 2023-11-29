/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:51 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/27 17:09:30 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	double	make_float_num(char *str, double num, double sign)
{
	double	div;

	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		if ((num > INT_MAX && sign == 1) || num * -1 < INT_MIN)
			return ((double) INT_MAX + 1);
		str++;
	}
	if (*str == '.')
		str++;
	div = 10;
	while (ft_isdigit(*str))
	{
		num += (*str - '0') / div;
		str++;
		div *= 10;
		if (div == 10000000)
			break ;
	}
	return (num * sign);
}

double	ft_atof(char *str)
{
	double	sign;
	double	num;

	num = 0.0;
	if (!str || !*str)
		return (0);
	while (*str == '\t' || *str == ' ' || *str == '\r' || *str == '\n')
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	num = make_float_num(str, num, sign);
	return (num);
}
