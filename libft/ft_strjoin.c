/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:02 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/15 12:37:05 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*result;

	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	result = (char *)malloc(s1l + s2l + 1);
	if (!result)
		return (0);
	result[0] = 0;
	ft_strlcat(result, (char *)s1, s1l + 1);
	ft_strlcat(result, (char *)s2, s1l + s2l + 1);
	return (result);
}
