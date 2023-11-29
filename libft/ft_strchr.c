/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:43:04 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 18:10:10 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;
	unsigned char	ucc;

	ucc = (unsigned char)c;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == ucc)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == ucc)
		return ((char *)(s + i));
	return (0);
}
