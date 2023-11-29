/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:31:38 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 19:03:37 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static char	*ft_bufadd_front(char *buf, char *str, int prec)
{
	char	*tempbuf;
	char	temp[2];
	char	*newbuf;

	if (buf == NULL || str == NULL)
		return (ft_nullguard(buf, str));
	if ((*buf == '+' || *buf == ' ' || *buf == '-') && prec && *buf)
	{
		temp[0] = *buf;
		temp[1] = '\0';
		tempbuf = ft_strjoin(temp, str);
	}
	else
	{
		tempbuf = ft_strdup(str);
		prec = 0;
	}
	if (tempbuf)
		newbuf = ft_strjoin(tempbuf, buf + prec);
	free(buf);
	free(str);
	if (tempbuf == NULL)
		return (NULL);
	free(tempbuf);
	return (newbuf);
}

static char	*ft_add_buf(char *buf, t_printf_flag flag, int num)
{
	if (buf == NULL)
		return (NULL);
	if (flag.zero && (flag.width > (int)ft_strlen(buf)))
		buf = ft_bufadd_front(buf,
				ft_addlen_str('0', flag.width - (int)ft_strlen(buf), buf), 1);
	if (flag.precision + (num < 0 || flag.plus
			|| flag.space) > (int)ft_strlen(buf))
		buf = ft_bufadd_front(buf, ft_addlen_str('0',
					flag.precision + (num < 0 || flag.plus
						|| flag.space) - (int)ft_strlen(buf), buf), 1);
	if ((flag.width > (int)ft_strlen(buf)) && !flag.hyphen)
		buf = ft_bufadd_front(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf), 0);
	if ((flag.width > (int)ft_strlen(buf)) && flag.hyphen)
		buf = ft_bufadd_back(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf));
	return (buf);
}

int	ft_print_d_bonus(const char *fmt, int num)
{
	t_printf_flag	flag;
	char			*buf;
	int				byte;

	ft_memset(&flag, 0, sizeof(t_printf_flag));
	flag = ft_setflag(fmt, flag);
	if (flag.zero && (flag.hyphen || flag.precision >= 0))
		flag.zero = 0;
	if (!flag.precision && !num)
		buf = (char *)ft_calloc(sizeof(char), 1);
	else
		buf = ft_itoa(num);
	if (flag.space && num >= 0 && !flag.plus)
		buf = ft_bufadd_front(buf, ft_addlen_str(' ', 1, buf), 0);
	if (flag.plus && num >= 0)
		buf = ft_bufadd_front(buf, ft_addlen_str('+', 1, buf), 0);
	buf = ft_add_buf(buf, flag, num);
	if (buf == NULL)
		return (-1);
	byte = write (1, buf, ft_strlen(buf));
	free(buf);
	return (byte);
}
