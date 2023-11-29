/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:23:46 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 12:10:06 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2 && !i)
			i = (int)(*(unsigned char *)s1 - *(unsigned char *)s2);
		n--;
		if (!n)
			break ;
		s1++;
		s2++;
	}
	return (i);
}
