/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:53:58 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/19 17:38:49 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_return_null(char *ptr)
{
	ptr = (char *)malloc(sizeof(char));
	if (ptr == NULL)
		return (NULL);
	*ptr = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_return_null(ptr));
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
