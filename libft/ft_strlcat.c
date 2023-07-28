/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:23:48 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/14 16:15:23 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	dest_len;
	size_t	src_len;
	size_t	result;

	i = 0;
	k = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	result = src_len + dest_len;
	if (dest_len > size)
		return (src_len + size);
	while (dest[i])
		i++;
	while (src[k] != '\0' && k + dest_len + 1 < size)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	dest[i] = '\0';
	return (result);
}
