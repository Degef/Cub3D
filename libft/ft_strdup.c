/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:59:59 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 13:59:59 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	char	*temp;
	int		s_len;

	s_len = ft_strlen(s);
	new_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	temp = new_str;
	while (*s)
	{
		*temp = *s;
		temp++;
		s++;
	}
	*temp = '\0';
	return (new_str);
}

// int main()
// {
// 	char *str = "helo world ";
// 	printf("%s", strdup(str));
// 	printf("\n%s", ft_strdup(str));
// }
