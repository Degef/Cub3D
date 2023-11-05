/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:55:28 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 12:55:28 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int main()
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	char *s = "3";
// 	lst->content = s;
// 	lst->next = malloc(sizeof(t_list));
// 	lst->next->content = s;
// 	lst->next->next = NULL;
// 	printf("%d", ft_lstsize(lst));
// }