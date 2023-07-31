#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

int main(void)
{
    char    **temp;

    temp = (char **)malloc(sizeof(char*) * 2);
    temp[0] = ft_strdup("cat");
    temp[1] = ft_strdup("test");
    execve("/bin/cat", temp, NULL);

}