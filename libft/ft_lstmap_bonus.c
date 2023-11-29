/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: millar <millar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:49:59 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/17 23:29:16 by millar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_add_lst(
	t_list *lst, void *(*f)(void *), void (*del)(void *), t_list **head)
{
	t_list	*temp;
	void	*ptr;

	while (lst)
	{
		ptr = f(lst->content);
		temp = ft_lstnew(ptr);
		if (temp == NULL)
		{
			del(ptr);
			break ;
		}
		ft_lstadd_back(head, temp);
		lst = lst->next;
	}
	if (temp == NULL)
		ft_lstclear(head, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*ptr;

	if (!lst)
		return (NULL);
	ptr = f(lst->content);
	head = ft_lstnew(ptr);
	if (head == NULL)
	{
		del(ptr);
		return (NULL);
	}
	if (!lst->next)
		return (head);
	ft_add_lst(lst->next, f, del, &head);
	return (head);
}
