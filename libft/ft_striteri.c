/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:32:50 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/16 21:37:01 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	len;
	size_t	i;
	char	*temp;

	i = 0;
	temp = s;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, temp++);
		i++;
	}
}
