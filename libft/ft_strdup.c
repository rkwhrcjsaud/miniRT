/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:44:59 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/21 15:34:23 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	n;
	size_t	i;

	if (!s1)
		return (NULL);
	n = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (0);
	i = 0;
	if (n + 1 != 0)
	{
		while (i < n)
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[n] = '\0';
	}
	return (ptr);
}
