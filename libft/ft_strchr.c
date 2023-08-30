/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:58:35 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 13:58:35 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c >= 256)
		c = c % 256;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return ((0));
}

// int main()
// {
// 	char s[] = "tripouille";
// 	// char c = ;
// 	printf("%s",strchr(s, 't' + 255));
// 	printf("\n%s", ft_strchr(s, 't' + 255));
// }