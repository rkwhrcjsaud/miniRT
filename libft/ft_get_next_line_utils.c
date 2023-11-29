/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:35:18 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/21 12:45:09 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strdup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!s1)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
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

char	*gnl_strjoin(t_gnl_list **node, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*ptr;

	len1 = gnl_strlen((*node)->line);
	len2 = gnl_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		ptr[i] = ((*node)->line)[i];
		i++;
	}
	while (i < len1 + len2)
	{
		ptr[i] = s2[i - len1];
		i++;
	}
	ptr[i] = '\0';
	free((*node)->line);
	(*node)->line = NULL;
	return (ptr);
}

size_t	gnl_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ucc;

	if (!s)
		return (0);
	ucc = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ucc)
			return (i + 1);
		i++;
	}
	if (s[i] == ucc)
		return (i + 1);
	return (0);
}

t_gnl_list	*gnl_lstnew(int fd)
{
	t_gnl_list	*node;

	node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (node == NULL)
		return (NULL);
	node->eof = 0;
	node->fd = fd;
	node->line = NULL;
	node->next = NULL;
	return (node);
}
