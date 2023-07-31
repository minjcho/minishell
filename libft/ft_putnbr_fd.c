/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:39:55 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/21 20:09:24 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itern(long long num, int fd)
{
	if (num > 9)
		ft_itern(num / 10, fd);
	write (fd, &"0123456789"[num % 10], 1);
}	

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	if (!n)
	{
		write (fd, "0", 1);
		return ;
	}
	num = (long long)n;
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	ft_itern(num, fd);
}
