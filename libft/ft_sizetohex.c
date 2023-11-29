/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizetohex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:04:43 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/20 20:26:18 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_sizetohex_len(size_t n)
{
	size_t	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

char	*ft_sizetohex(size_t n, unsigned char isbig)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_sizetohex_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	if (!n)
		ptr[0] = '0';
	i = 0;
	while (n)
	{
		if (n % 16 <= 9)
			ptr[len - i - 1] = n % 16 + '0';
		else
			ptr[len - i - 1] = n % 16 + ('a' * (!isbig)) + ('A' * (isbig)) - 10;
		n /= 16;
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}
