/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:17:10 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 18:17:10 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		exit(1);
	del(lst->content);
	free(lst);
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	lst->content = (char *)"hello";
// 	lst->next = malloc(sizeof(t_list));
// 	lst->next->content = (char *)"world";
// 	lst->next->next = NULL;
// 	ft_lstdelone(lst, *del);
// 	t_list *curr = lst;
// 	while (curr != NULL)
// 	{
// 		printf("%s", (char *)curr->content);
// 		curr = curr->next;
// 	}
// }
