/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:28:50 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 18:28:50 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*temp;
// 	t_list	*result;
// 	while (lst)
// 	{
// 		temp = ft_lstnew(f(lst->content));
// 		if (!temp)
// 		{
// 			ft_lstclear(&result, del);
// 			return (0);
// 		}
// 		ft_lstadd_back(&result, temp);
// 		lst = lst->next;
// 	}
// 	return (result);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (!temp)
		{
			while (result)
			{
				temp = result->next;
				(*del)(result->content);
				free(result);
				result = temp;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&result, temp);
		lst = lst->next;
	}
	return (result);
}
