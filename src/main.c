/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/27 20:10:54 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipe='|'

// 1. echo a | wc -l
//    1. "echo a"
//    2. "wc -l"
   

// 2. echo a $pipe wc -l
//    1. "echo a $pipe wc -l"
//       "echo" "a" "|" "wc" "-l"

int main(int ac, char **av, char ** envp)
{
    //init;
    t_mini  mini;
    mini.command = "cd";
    mini.option = NULL;
    mini.option_cnt = 0;
}