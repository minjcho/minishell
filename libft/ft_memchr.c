/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:32:56 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/17 11:48:59 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		tempc;
	const unsigned char	*temps;
	size_t				i;

	tempc = (unsigned char)c;
	temps = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temps[i] == tempc)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
