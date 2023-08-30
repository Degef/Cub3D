/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:25:37 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 13:25:37 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = (unsigned char)c;
	return (s);
}
// int main()
// {

// 	char st[50];
// 	char str[50];

// 	memset(st, '$', 10);
// 	printf("%s", st);
// 	ft_memset(str, '$', 10);
// 	printf("\n%s", str);
// 	return (0);
// }