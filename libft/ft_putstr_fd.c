/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:59:35 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 17:51:02 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

#define WRITE_BYTES 1024

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	ssize_t	written_bytes;
	size_t	total_bytes;
	size_t	remain;

	if (!s)
		return ;
	total_bytes = 0;
	len = ft_strlen(s);
	while (total_bytes < len)
	{
		remain = len - total_bytes;
		if (!remain)
			break ;
		else if (remain < WRITE_BYTES)
			written_bytes = write (fd, s + total_bytes, remain);
		else
			written_bytes = write (fd, s + total_bytes, WRITE_BYTES);
		if (written_bytes < 0)
			break ;
		total_bytes += written_bytes;
	}
}
