/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjcho <minjcho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:35:16 by minjcho           #+#    #+#             */
/*   Updated: 2023/07/28 16:53:58 by minjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *charset, char to_find)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == to_find)
			return (1);
		i++;
	}
	if (to_find == '\0')
		return (1);
	return (0);
}

int	get_size(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_in(charset, str[i]) == 0
			&& is_in(charset, str[i + 1]) == 1)
			count++;
		i++;
	}
	return (count);
}

void	put_words(char *tmp, char *str, char *charset)
{
	int	i;

	i = 0;
	while (is_in(charset, str[i]) == 0)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
}

void	split_words(char **tmp, char *str, char *charset)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	idx = 0;
	while (str[i])
	{
		if (is_in(charset, str[i]))
			i++;
		else
		{
			j = 0;
			while (is_in(charset, str[i + j]) == 0)
				j++;
			tmp[idx] = (char *)malloc(sizeof(char) * (j + 1));
			put_words(tmp[idx], &str[i], charset);
			i = i + j;
			idx++;
		}
	}
}

char	**ft_split2(char *str, char *charset)
{
	char	**tmp;
	int		size;

	size = get_size(str, charset);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	split_words(tmp, str, charset);
	tmp[size] = 0;
	return (tmp);
}
