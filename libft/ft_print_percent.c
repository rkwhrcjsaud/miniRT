/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:18:10 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 18:59:58 by gibkim           ###   ########.fr       */
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

int	ft_print_percent_bonus(const char *fmt)
{
	t_printf_flag	flag;
	char			*buf;
	int				byte;

	ft_memset(&flag, 0, sizeof(t_printf_flag));
	flag = ft_setflag(fmt, flag);
	buf = (char *)malloc(sizeof(char) * 2);
	if (buf == NULL)
		return (-1);
	buf[0] = '%';
	buf[1] = '\0';
	buf = ft_add_buf(buf, flag);
	if (buf == NULL)
		return (-1);
	byte = write(1, buf, ft_strlen(buf));
	free(buf);
	return (byte);
}
