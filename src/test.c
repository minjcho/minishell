#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

int main(void)
{
    char    **temp;

    temp = (char **)malloc(sizeof(char*) * 4);
    temp[1] = NULL;
    temp[0] = ft_strdup("cat");
    temp[2] = ft_strdup("test");
    temp[3] = NULL;
    execve("/bin/cat", temp, NULL);

}