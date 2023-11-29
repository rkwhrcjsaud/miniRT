/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:34:18 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/20 17:36:41 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_uitoa_len(unsigned int n)
{
	size_t	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_uitoa_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	if (!n)
		ptr[0] = '0';
	i = 0;
	while (n)
	{
		ptr[len - i - 1] = n % 10 + '0';
		n /= 10;
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}
