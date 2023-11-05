/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:10:43 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 12:10:43 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n--)
	{
		((unsigned char *)s)[i++] = '\0';
	}
}

// int main()
// {

// 	char str[50] = "Hello world";
// 	// bzero(str, 4);
// 	ft_bzero(&str, 4);
// 	printf("%s", str);
// }