/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:15:30 by mkiflema          #+#    #+#             */
/*   Updated: 2022/12/24 16:15:30 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*start_str;
	char	*end_str;

	if (!s1)
		return (0);
	start_str = (char *)s1;
	end_str = start_str + ft_strlen(s1);
	while (*start_str != 0 && ft_strchr(set, *start_str))
		start_str++;
	while ((start_str < end_str) && ft_strchr(set, *(end_str - 1)))
		end_str--;
	result = ft_substr(start_str, 0, end_str - start_str);
	return (result);
}

// int main()
// {
// 	char *s1 = "Helolo";
// 	char *set = "Hoe";
// 	printf("%s", ft_strtrim(s1, set));
// }