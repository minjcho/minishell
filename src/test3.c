#include <stdio.h>
#include "../include/minishell.h"

int main(void)
{
    char    *temp = "AA";
    char    *target = "AAA";
    if (ft_strncmp(target, temp, ft_strlen(target)) == 0)
        printf("is start");
}