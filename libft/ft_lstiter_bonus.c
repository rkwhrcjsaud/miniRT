/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:39:38 by gibkim            #+#    #+#             */
/*   Updated: 2023/03/15 21:00:53 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	size_t	size;
	size_t	i;

	size = ft_lstsize(lst);
	i = 0;
	while (i < size)
	{
		f(lst->content);
		lst = lst->next;
		i++;
	}
}
