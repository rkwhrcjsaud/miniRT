/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:06:01 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 19:03:57 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static char	*ft_bufadd_front(char *buf, char *str, int prec, t_printf_flag flag)
{
	char	*tempbuf;
	char	temp[2];
	char	*newbuf;

	if (buf == NULL || str == NULL)
		return (ft_nullguard(buf, str));
	if ((*buf == ' ') && flag.space && prec && *buf)
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

static char	*ft_add_buf(char *buf, t_printf_flag flag)
{
	if (buf == NULL)
		return (NULL);
	if (flag.zero && flag.hyphen)
		flag.zero = 0;
	if (flag.zero && (flag.width > (int)ft_strlen(buf)))
		buf = ft_bufadd_front(buf,
				ft_addlen_str('0', flag.width
					- (int)ft_strlen(buf), buf), 1, flag);
	if ((flag.width > (int)ft_strlen(buf)) && !flag.hyphen)
		buf = ft_bufadd_front(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf), 0, flag);
	if ((flag.width > (int)ft_strlen(buf)) && flag.hyphen)
		buf = ft_bufadd_back(buf, ft_addlen_str(' ',
					flag.width - (int)ft_strlen(buf), buf));
	return (buf);
}

static int	ft_print(unsigned int num, char *buf, t_printf_flag flag)
{
	int	byte;

	if (!num && flag.hyphen)
		if (write(1, "", 1) < 0)
			return (-1);
	byte = write (1, buf, ft_strlen(buf));
	if (byte < 0)
		return (-1);
	if (!num && !flag.hyphen)
		if (write(1, "", 1) < 0)
			return (-1);
	if (!num)
		byte++;
	return (byte);
}

int	ft_print_c_bonus(const char *fmt, unsigned int num)
{
	t_printf_flag	flag;
	char			*buf;
	int				byte;

	ft_memset(&flag, 0, sizeof(t_printf_flag));
	flag = ft_setflag(fmt, flag);
	buf = (char *)malloc(sizeof(char) * 2);
	if (buf == NULL)
		return (-1);
	buf[0] = (unsigned char)num;
	buf[1] = '\0';
	if (!num)
		flag.width -= (flag.width > 0);
	buf = ft_add_buf(buf, flag);
	if (buf == NULL)
		return (-1);
	byte = ft_print(num, buf, flag);
	free(buf);
	return (byte);
}
