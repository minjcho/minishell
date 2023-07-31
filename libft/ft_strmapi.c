/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:55:51 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/20 17:25:52 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	size_t			k;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	k = 0;
	if (!f)
		return (0);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	while (k < len)
	{
		result[i] = f(i, s[i]);
		i++;
		k++;
	}
	result[i] = 0;
	return (result);
}
