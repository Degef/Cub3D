/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:03:30 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 13:03:30 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	if (c >= 256)
		c = c % 256;
	while (n--)
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	return (0);
}

// int main()
// {
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	//char c = 'e';
// 	char *result;
// 	result = memchr(s, 2, 3);
// 	printf("%s", result);
// 	result = ft_memchr(s, 2 + 256, 3);
// 	printf("\n%s", result);
// }