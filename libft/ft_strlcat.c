/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:01:06 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/19 20:00:53 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	destlen = ft_strlen(dst);
	if (dstsize < destlen)
		return (dstsize + srclen);
	i = 0;
	while (destlen + i < dstsize - 1 && src[i])
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
