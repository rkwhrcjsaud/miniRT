/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:32:36 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 20:33:04 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_search_end(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	while (len - 1 > 0)
	{
		i = 0;
		while (set[i])
		{
			if (s1[len - 1] == set[i])
				break ;
			i++;
		}
		if (i == ft_strlen(set))
			break ;
		len--;
	}
	return (len);
}

static const char	*ft_search_start(char const *s1, char const *set)
{
	size_t	i;

	if (!set)
		return (NULL);
	while (*s1)
	{
		i = 0;
		while (set[i])
		{
			if (*s1 == set[i])
				break ;
			i++;
		}
		if (i == ft_strlen(set))
			break ;
		s1++;
	}
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	char		*ptr;
	size_t		len;
	const char	*cs1;

	if (!s1)
		return (NULL);
	if (!*set)
		return (ft_strdup(s1));
	cs1 = s1;
	cs1 = ft_search_start(cs1, set);
	if (*cs1 == 0)
		return (ft_strdup(""));
	len = ft_search_end(cs1, set);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = cs1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>
int	main(void)
{
	char const	*str1 = "acbacabca";
	char const	*str2 = "acaabaaca";
	char const	*str3 = "";
	char const	*str4 = NULL;
	char const	*str5 = "accca";
	char const	*set1 = "a";
	char const	*set2 = "ca";
	char const	*set3 = "";
	char const	*set4 = NULL;
	
	printf("%s %s\n", "[\"acbacabca\", \"a\"]\nexpect : cbacabc\nresult :",
		ft_strtrim(str1, set1));
	printf("%s %s\n", "[\"acaabaaca\", \"a\"]\nexpect : caabaac\nresult :",
		ft_strtrim(str2, set1));
	printf("%s %s\n", "[\"\", \"a\"]\nexpect : \nresult :",
		ft_strtrim(str3, set1));
	printf("%s %s\n", "[NULL, \"a\"]\nexpect : (null)\nresult :",
		ft_strtrim(str4, set1));
	printf("%s %s\n\n", "[\"accca\", \"a\"]\nexpect : ccc\nresult :",
		ft_strtrim(str5, set1));
	printf("%s %s\n", "[\"acbacabca\", \"ca\"]\nexpect : bacab\nresult :",
		ft_strtrim(str1, set2));
	printf("%s %s\n", "[\"acaabaaca\", \"ca\"]\nexpect : b\nresult :",
		ft_strtrim(str2, set2));
	printf("%s %s\n", "[\"\", \"ca\"]\nexpect : \nresult :",
		ft_strtrim(str3, set2));
	printf("%s %s\n", "[NULL, \"ca\"]\nexpect : (null)\nresult :",
		ft_strtrim(str4, set2));
	printf("%s %s\n\n", "[\"accca\", \"ca\"]\nexpect : \nresult :",
		ft_strtrim(str5, set2));
	printf("%s %s\n", "[\"acbacabca\", \"\"]\nexpect : acbacabca\nresult :",
		ft_strtrim(str1, set3));
	printf("%s %s\n\n", "[\"acaabaaca\", \"\"]\nexpect : acaabaaca\nresult :",
		ft_strtrim(str2, set3));
	printf("%s %s\n", "[\"acbacabca\", NULL]\nexpect : acbacabca\nresult :",
		ft_strtrim(str1, set3));
	printf("%s %s\n", "[\"acaabaaca\", NULL]\nexpect : acaabaaca\nresult :",
		ft_strtrim(str2, set3));
}
*/