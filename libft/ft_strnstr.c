/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:32:02 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/20 16:41:41 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr_2(const char *h, const char *n, size_t len, size_t i)
{
	size_t	k;

	k = 0;
	while (*h == *n && *h && *n && i + k < len)
	{
		h++;
		n++;
		k++;
	}
	if (!*n)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*htemp;
	const char	*ntemp;
	size_t		i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (0);
	while (i < len && *haystack)
	{
		if (*haystack == *needle)
		{
			htemp = haystack;
			ntemp = needle;
			if (ft_strnstr_2(htemp, ntemp, len, i))
				return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (0);
}
