/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:31:29 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/19 11:22:00 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	ucc;

	if (c > 255 || c < 0)
		return (c);
	ucc = (unsigned char)c;
	if (ucc >= 'a' && ucc <= 'z')
		ucc -= 32;
	return (ucc);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	num = 99 + 256;

	printf("number is %d and char is %c\nft_toupper_c -> %c\n", num, num,
		ft_toupper(num));
	printf("ft_toupper_d -> %d\n", ft_toupper(num));
	printf("toupper_c -> %c\n", toupper(num));
	printf("toupper_d -> %d\n", toupper(num));
}
*/
