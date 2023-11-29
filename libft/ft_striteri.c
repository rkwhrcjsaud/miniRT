/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:29:35 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 20:49:34 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return ;
	len = (unsigned int)ft_strlen(s);
	i = 0;
	while (i < len)
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
void	function(unsigned int i, char *str)
{
	*str = *str + i;
}

int	main(void)
{
	char	s1[6] = "aaaaa";
	char	s2[1] = "";
	char	*s3 = NULL;

	printf("\n%s\n", "[\"aaaaa\"]\n\nexpect : abcde");
	ft_striteri(s1, function);
	printf("%s %s\n\n", "result :", s1);
	printf("%s\n", "[\"\"]\n\nexpect : ");
	ft_striteri(s2, function);
	printf("%s %s\n\n", "result :", s2);
	printf("%s\n", "[NULL]\n\nexpect : (null)");
	ft_striteri(s3, function);
	printf("%s %s\n\n", "result :", s3);
}
*/
