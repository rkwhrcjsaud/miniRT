/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:24:02 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 19:00:06 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static char	*ft_bufadd_front(char *buf, char *str)
{
	char	*newbuf;

	if (buf == NULL || str == NULL)
		return (ft_nullguard(buf, str));
	newbuf = ft_strjoin(str, buf);
	free(buf);
	free(str);
	return (newbuf);
}

static char	*ft_add_buf(char *buf, t_printf_flag flag)
{
	if (flag.zero && (flag.hyphen || flag.precision >= 0))
		flag.zero = 0;
	if (buf == NULL)
		return (NULL);
	if (flag.zero && (flag.width > (int)ft_strlen(buf)))
		buf = ft_bufadd_front(buf,
				ft_addlen_str('0', flag.width - (int)ft_strlen(buf), buf));
	if (flag.precision > (int)ft_strlen(buf))
		buf = ft_bufadd_front(buf, ft_addlen_str('0',
					flag.precision - (int)ft_strlen(buf), buf));
	if ((flag.width > (int)ft_strlen(buf)) && !flag.hyphen)
		buf = ft_bufadd_front(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf));
	if ((flag.width > (int)ft_strlen(buf)) && flag.hyphen)
		buf = ft_bufadd_back(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf));
	return (buf);
}

int	ft_print_u_bonus(const char *fmt, unsigned int num)
{
	t_printf_flag	flag;
	char			*buf;
	int				byte;

	ft_memset(&flag, 0, sizeof(t_printf_flag));
	flag = ft_setflag(fmt, flag);
	if (!flag.precision && !num)
		buf = (char *)ft_calloc(sizeof(char), 1);
	else
		buf = ft_uitoa(num);
	if (buf == NULL)
		return (-1);
	buf = ft_add_buf(buf, flag);
	if (buf == NULL)
		return (-1);
	byte = write (1, buf, ft_strlen(buf));
	free(buf);
	return (byte);
}
