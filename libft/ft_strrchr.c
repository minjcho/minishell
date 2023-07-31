/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:25:30 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/20 19:59:07 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			ret = (char *)&s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		ret = (char *)&s[i];
	return (ret);
}
