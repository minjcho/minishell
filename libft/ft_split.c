/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:31:34 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/03/16 19:21:09 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	word_cnt(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (!*s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
			break ;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			cnt++;
		i++;
	}
	if (s[i - 1] != c && s[i] == '\0')
		cnt++;
	return (cnt);
}

int	ft_free(char **result, size_t i)
{
	size_t	k;

	k = 0;
	if (!result[i])
	{
		while (k < i)
			free(result[k++]);
		free (result);
		return (1);
	}
	return (0);
}

size_t	ft_wlen(char const *s, char c, size_t wi)
{
	size_t	wl;

	wl = 0;
	while (s[wi])
	{
		if (s[wi] != c)
			wl++;
		else
			break ;
		wi++;
	}
	return (wl);
}

int	putword(char **result, char const *s, char c, size_t w)
{
	size_t	i;
	size_t	wi;
	size_t	wl;
	size_t	k;

	wi = 0;
	i = 0;
	while (i < w)
	{
		wl = 0;
		k = 0;
		while (s[wi] == c)
			wi++;
		wl = ft_wlen(s, c, wi);
		result[i] = (char *)malloc(wl + 1);
		if (ft_free(result, i))
			return (1);
		while (k < wl)
		{
			result[i][k] = s[wi++];
			k++;
		}
		result[i++][k] = 0;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	w;
	char	**result;

	w = word_cnt(s, c);
	result = (char **)malloc(sizeof(char *) * (w + 1));
	if (!result)
		return (0);
	result[w] = 0;
	if (putword(result, s, c, w))
		return (0);
	return (result);
}
