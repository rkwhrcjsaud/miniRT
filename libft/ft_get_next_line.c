/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:40:27 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/21 12:56:13 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "ft_get_next_line.h"

static void	ft_read(int fd, t_gnl_list **node)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	reading_bytes;
	char	*temp;

	reading_bytes = read(fd, buf, BUFFER_SIZE);
	if (reading_bytes < 0)
	{
		(*node)->eof = 2;
		return ;
	}
	else if (reading_bytes < BUFFER_SIZE)
		(*node)->eof = 1;
	buf[reading_bytes] = '\0';
	temp = gnl_strjoin(node, buf);
	(*node)->line = temp;
}

static char	*ft_get_line(t_gnl_list **node)
{
	char	*temp;
	char	*remain;
	size_t	nlen;

	nlen = gnl_strchr((*node)->line, '\n');
	remain = NULL;
	if (!nlen && (*node)->eof)
		temp = gnl_strdup((*node)->line, gnl_strlen((*node)->line));
	else
	{
		temp = gnl_strdup((*node)->line, nlen);
		if (nlen == gnl_strlen((*node)->line))
			remain = NULL;
		else
			remain = gnl_strdup((*node)->line + nlen,
					gnl_strlen((*node)->line) - nlen);
	}
	free((*node)->line);
	(*node)->line = remain;
	if (!*temp)
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static t_gnl_list	*ft_search_fd(t_gnl_list *head, int fd)
{
	t_gnl_list	*current;
	t_gnl_list	*node;

	current = head;
	while (current)
	{
		if (current->next == NULL)
			break ;
		if (current->next->fd == fd)
			return (current->next);
		current = current->next;
	}
	node = gnl_lstnew(fd);
	current->next = node;
	return (node);
}

static char	*ft_delnode(t_gnl_list *head, t_gnl_list **node)
{
	t_gnl_list	*front;

	front = head;
	while (front->next)
	{
		if (front->next == *node)
			break ;
		front = front->next;
	}
	front->next = (*node)->next;
	if ((*node)->line)
		free((*node)->line);
	(*node)->next = NULL;
	free(*node);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	head;
	t_gnl_list			*node;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	node = ft_search_fd(&head, fd);
	if (node == NULL)
		return (NULL);
	if (gnl_strchr(node->line, '\n') || node->eof)
	{
		if (node->line == NULL || *(node->line) == '\0')
			return (ft_delnode(&head, &node));
		else
			return (ft_get_line(&node));
	}
	ft_read(fd, &node);
	if (node->eof == 2)
		return (ft_delnode(&head, &node));
	if (node->line == NULL)
		return (ft_delnode(&head, &node));
	return (get_next_line(fd));
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*temp;

	fd = open("test.txt", O_RDONLY);
	temp = get_next_line(fd);
	printf("%s\n", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s\n", temp);
	free(temp);
	temp = get_next_line(fd);
	printf("%s\n", temp);
	free(temp);
}
*/