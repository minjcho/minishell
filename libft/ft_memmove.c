/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:12:15 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/14 15:59:49 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *str, size_t num)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !str)
		return (0);
	d = (unsigned char *)dest;
	s = (unsigned char *)str;
	i = 0;
	if (dest <= str)
	{
		while (i < num)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		d += num;
		s += num;
		while (num--)
			*(--d) = *(--s);
	}
	return (dest);
}
