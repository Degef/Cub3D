/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:06:38 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 13:06:38 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str_1;
	unsigned char	*str_2;
	size_t			i;

	i = 0;
	str_1 = (unsigned char *)s1;
	str_2 = (unsigned char *)s2;
	while ((i < n))
	{
		if (str_1[i] != str_2[i])
			return ((unsigned char)str_1[i] - (unsigned char)str_2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char	*s1 ="atoms\0\0\0\0";;
// 	char	*s2 ="atoms\0abc";
// 	size_t	size = 8;
// 	printf("%d", memcmp(s1, s2, size));
// 	printf("\n%d", ft_memcmp(s1, s2, size));
// }