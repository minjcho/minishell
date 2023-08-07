/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:51:51 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/08/07 20:52:03 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_deleter(t_mini *data)
{
	int	i;
	int	j;

	i = -1;
	if (!data->doc_cnt)
		return ;
	while (++i < data->cnt)
	{
		j = 0;
		while (data[i].temp_files[j])
		{
			if (unlink(data[i].temp_files[j]) != 0)
				//error_unlink();
			j++;
		}
	}
}