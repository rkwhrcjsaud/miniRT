/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:31:27 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/19 11:21:01 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	ucc;

	if (c > 255 || c < 0)
		return (c);
	ucc = (unsigned char)c;
	if (ucc >= 'A' && ucc <= 'Z')
		ucc += 32;
	return (ucc);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	num = 67;

	printf("number is %d and char is %c\nft_tolower_c -> %c\n", num, num,
		ft_tolower(num));
	printf("ft_tolower_d -> %d\n", ft_tolower(num));
	printf("tolower_c -> %c\n", tolower(num));
	printf("tolower_d -> %d\n", tolower(num));
}
*/
