/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:39:27 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 19:00:10 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_nullguard(char *buf, char *str)
{
	if (buf == NULL && str)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	else if (buf && str == NULL)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	else if (buf == NULL && str == NULL)
		return (NULL);
	return (NULL);
}

char	*ft_bufadd_back(char *buf, char *str)
{
	char	*newbuf;

	if (buf == NULL || str == NULL)
		return (NULL);
	newbuf = ft_strjoin(buf, str);
	free(buf);
	free(str);
	if (newbuf == NULL)
		return (NULL);
	return (newbuf);
}

char	*ft_addlen_str(char c, int len, char *buf)
{
	char	*str;
	int		i;

	i = 0;
	if (buf == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	str[len] = '\0';
	return (str);
}

size_t	ft_format_case(const char *format)
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
	return (i);
}
