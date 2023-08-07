#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>

int main(void)
{
    // char    **temp;

    // temp = (char **)malloc(sizeof(char*) * 4);
    // temp[1] = NULL;
    // temp[0] = ft_strdup("cat");
    // temp[2] = ft_strdup("test");
    // temp[3] = NULL;
    // execve("/bin/cat", temp, NULL);
    char    *str;
    int i;

    str = "/Users/jinhyeok/goinfre/1";
    i = open(str, O_CREAT | O_WRONLY ,0644);
    if (i == -1)
        write(2, "Errr", 4);
}