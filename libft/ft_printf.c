/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:37:13 by gibkim            #+#    #+#             */
/*   Updated: 2023/05/14 19:47:55 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static int	ft_print(const char *format, va_list *ap)
{
	int	specifier;

	specifier = format[ft_format_case(format)];
	if (specifier == '%')
		return (ft_print_percent_bonus(format));
	else if (specifier == 'c')
		return (ft_print_c_bonus(format, va_arg(*ap, unsigned int)));
	else if (specifier == 's')
		return (ft_print_s_bonus(format, va_arg(*ap, char *)));
	else if (specifier == 'p')
		return (ft_print_p_bonus(format, va_arg(*ap, size_t)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_d_bonus(format, va_arg(*ap, int)));
	else if (specifier == 'u')
		return (ft_print_u_bonus(format, va_arg(*ap, unsigned int)));
	else if (specifier == 'x')
		return (ft_print_sx_bonus(format, va_arg(*ap, unsigned int)));
	else if (specifier == 'X')
		return (ft_print_bx_bonus(format, va_arg(*ap, unsigned int)));
	else if (specifier == 0)
		return (0);
	return (-1);
}

static int	ft_next_spec(const char *format)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (format[i])
	{
		j = 0;
		while (SPECIFIERS[j])
		{
			if (format[i] == SPECIFIERS[j])
				break ;
			j++;
		}
		if (SPECIFIERS[j])
			break ;
		i++;
	}
	if (!format[i])
		return (i);
	return (i + 1);
}

static int	ft_vaend(va_list *ap)
{
	va_end(*ap);
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		print_bytes;
	int		current;

	print_bytes = 0;
	va_start(ap, format);
	while (*format)
	{
		while (*format != '%' && *format)
		{
			if ((write (1, format++, 1) < 0))
				return (ft_vaend(&ap));
			print_bytes++;
		}
		if (*format == '%' && *format)
		{
			current = ft_print(++format, &ap);
			if (current < 0)
				return (ft_vaend(&ap));
			print_bytes += current;
			format += ft_next_spec(format);
		}
	}
	va_end(ap);
	return (print_bytes);
}
