/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:03:08 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/17 17:49:14 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_putnbr_rec(int n, int fd)
{
	char	c;

	if (n)
	{
		ft_putnbr_rec(n / 10, fd);
		c = ft_abs(n % 10) + '0';
		write (fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write (fd, "-", 1);
	if (!n)
		write (fd, "0", 1);
	else
		ft_putnbr_rec(n, fd);
}
