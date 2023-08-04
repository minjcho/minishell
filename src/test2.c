#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
char    **environ;

int main(void)
{
    pid_t id;
    char    *temp[] = {"./test3", NULL};

    id = fork();
    if (id == 0)
    {
        if (execve("./test3", temp, environ) == - 1)
            printf("test");
    }
    else if (id > 0)
    {
        wait(NULL);
    }

}