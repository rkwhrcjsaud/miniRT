/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:48:40 by gibkim            #+#    #+#             */
/*   Updated: 2023/05/12 14:55:05 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_gnl_list
{
	int					fd;
	char				*line;
	int					eof;
	struct s_gnl_list	*next;
}	t_gnl_list;

size_t		gnl_strlen(const char *s);
char		*gnl_strdup(const char *s1, size_t n);
char		*gnl_strjoin(t_gnl_list **node, char *s2);
size_t		gnl_strchr(const char *s, int c);
t_gnl_list	*gnl_lstnew(int fd);
char		*get_next_line(int fd);

#endif