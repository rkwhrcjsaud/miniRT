/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:00:16 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/19 17:57:18 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while (len > 0)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (haystack[i] && needle[i])
			{
				if (haystack[i] == needle[i])
					i++;
				else
					break ;
			}
			if (needle[i] == '\0' && i <= len)
				return ((char *)haystack);
		}
		if (--len && *haystack)
			haystack++;
	}
	return (0);
}
