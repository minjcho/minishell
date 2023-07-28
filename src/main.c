/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:33:41 by jinhyeok          #+#    #+#             */
/*   Updated: 2023/07/27 21:09:23 by jinhyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

// pipe='|'

// 1. echo a | wc -l
//    1. "echo a"
//    2. "wc -l"
   

// 2. echo a $pipe wc -l
//    1. "echo a $pipe wc -l"
//       "echo" "a" "|" "wc" "-l"

int main(int ac, char **av)
{
    //init;
    (void)ac;
    (void)av;
    printf("%s", environ[0]);
}