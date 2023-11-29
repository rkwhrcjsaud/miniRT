/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:03:28 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 18:05:42 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_count_word(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s)
				s++;
			cnt++;
		}
	}
	return (cnt);
}	

static char	*ft_word(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	**ft_free(char **pptr, size_t i)
{
	while (i + 1)
	{
		if (pptr[i])
			free(pptr[i]);
		pptr[i] = NULL;
		if (!i)
			break ;
		i--;
	}
	free(pptr);
	pptr = NULL;
	return (NULL);
}

static char	**ft_add_word(char const *s, char c, char **pptr, size_t cnt)
{
	size_t	i;
	char	to_free;

	i = 0;
	to_free = 0;
	while (i < cnt)
	{
		if (*s == c && *s)
			s++;
		else
		{
			pptr[i] = ft_word(s, c);
			if (!pptr[i++])
			{
				to_free = 1;
				break ;
			}
			while (*s != c && *s)
				s++;
		}
	}
	pptr[i] = 0;
	if (to_free)
		pptr = ft_free(pptr, i - 1);
	return (pptr);
}

char	**ft_split(char const *s, char c)
{
	char	**pptr;
	size_t	cnt;

	if (!s)
		return (NULL);
	cnt = ft_count_word(s, c);
	pptr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (pptr == NULL)
		return (NULL);
	pptr = ft_add_word(s, c, pptr, cnt);
	return (pptr);
}
