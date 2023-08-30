/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:51:56 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 15:51:56 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	int				len;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s[i] != '\0')
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char f(unsigned int i, char c)
// {
// 	char ca;
// 	ca = c + i;
// 	return (ca);
// }

// int main()
// {
// 	char *str = "hello";
// 	printf("%s", ft_strmapi(str, *f));
// }
