/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:24:49 by mkiflema          #+#    #+#             */
/*   Updated: 2023/09/22 21:26:36 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// int	ft_isdigit(int c)
// {
// 	if (c < '0' || c > '9')
// 		return (0);
// 	return (c);
// }

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}


// int main(){
// 	printf("%c", ft_isdigit(':'));
// }