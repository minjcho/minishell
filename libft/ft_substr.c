/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:41:54 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/16 20:52:35 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	sub2(size_t len, unsigned int slen, unsigned int start)
{
	unsigned int	result;

	result = 0;
	if (!len || !slen || slen < start)
		return (0);
	if (len > slen)
		result = slen;
	else
		result = len;
	if (slen < len + start)
		result = slen - start;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	slen;
	size_t			i;

	i = 0;
	slen = ft_strlen(s);
	result = (char *)malloc(sub2(len, slen, start) + 1);
	if (!result)
		return (0);
	if (slen < start || !*s)
	{
		result[0] = 0;
		return (result);
	}
	while (i < len && start < slen)
	{
		result[i++] = s[start];
		start++;
	}
	result[i] = '\0';
	return (result);
}
