/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:16:27 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/16 20:53:08 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_intlen(long long num, long long sign)
{
	long long	len;

	len = 0;
	while (num)
	{
		len++;
		num /= 10;
	}
	if (sign == -1)
		len++;
	return (len);
}

void	ft_strrev(char *result)
{
	size_t	len;
	char	temp;
	size_t	i;

	len = ft_strlen(result);
	i = 0;
	while (i < len / 2)
	{
		temp = result[i];
		result[i] = result[len - i - 1];
		result[len - i++ - 1] = temp;
	}
}

char	*ft_mal(char *result, long long num, long long sign)
{
	size_t	i;

	i = 0;
	result = (char *)malloc(ft_intlen(num, sign) + 1);
	if (!result)
		return (0);
	while (num)
	{
		result[i++] = num % 10 + 48;
		num /= 10;
	}
	if (sign == -1)
		result[i++] = '-';
	result[i] = 0;
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	long long	num;
	long long	sign;

	sign = 1;
	result = 0;
	num = (long long)n;
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	if (!num)
		return (ft_strdup("0"));
	result = ft_mal(result, num, sign);
	if (!result)
		return (0);
	ft_strrev(result);
	return (result);
}
