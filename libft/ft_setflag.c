/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:54:33 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 19:00:17 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_printf_flag	ft_set_width(t_printf_flag flag,
	const char *fmt, size_t max)
{
	size_t	i;

	if (max == 0)
		return (flag);
	i = max - 1;
	while (1)
	{
		if (fmt[i] >= '0' && fmt[i] <= '9')
		{
			while (fmt[i] >= '0' && fmt[i] <= '9' && i != 0)
				i--;
			if (fmt[i] != '.')
			{
				flag.width = ft_atoi(&fmt[i + (i != 0
							|| !(fmt[i] >= '0' && fmt[i] <= '9'))]);
				return (flag);
			}
		}
		if (!i)
			break ;
		i--;
	}
	return (flag);
}

static t_printf_flag	ft_set_precision(t_printf_flag flag,
	const char *fmt, size_t max)
{
	size_t	i;

	if (fmt[0] == '0')
		flag.zero = 1;
	if (max == 0)
		return (flag);
	i = max - 1;
	while (1)
	{
		if (fmt[i] == '.')
		{
			flag.precision = ft_atoi(&fmt[i + 1]);
			break ;
		}
		if (!i)
			break ;
		i--;
	}
	return (flag);
}

t_printf_flag	ft_setflag(const char *fmt, t_printf_flag flag)
{
	size_t	max;
	size_t	i;

	max = ft_format_case(fmt);
	flag.precision = -1;
	i = 0;
	while (i < max)
	{
		if (fmt[i] == '-')
			flag.hyphen = 1;
		if (i > 0 && fmt[i] == '0')
			if (!((fmt[i - 1] > 47 && fmt[i - 1] < 58) || fmt[i - 1] == '.'))
				flag.zero = 1;
		if (fmt[i] == ' ')
			flag.space = 1;
		if (fmt[i] == '+')
			flag.plus = 1;
		if (fmt[i] == '#')
			flag.hash = 1;
		if (fmt[i++] == '.')
			flag.precision = 0;
	}
	flag = ft_set_width(flag, fmt, max);
	flag = ft_set_precision(flag, fmt, max);
	return (flag);
}
