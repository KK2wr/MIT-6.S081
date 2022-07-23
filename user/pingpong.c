#include "kernel/types.h"
#include "user/user.h"
   
#define READ 0
#define WRITEE 1

int main(int argc, char *argv[])
{
    int p1[2], p2[2];
    int pid;
    char rec[1];
    char send[1] = {' '};
    pipe(p1); pipe(p2);
    pid = fork();
    if (pid < 0)
    {
        fprintf(2, "fork error\n");
        exit(1);
    }
    if (pid == 0)
    {
        //child
        close(p1[WRITEE]);
        close(p2[READ]);
        read(p1[READ], rec, 1);
        fprintf(1, "%d:received ping\n", getpid());
        write(p2[WRITEE], send, 1);
        close(p1[WRITEE]);
        close(p2[WRITEE]);
        exit(0);
    }
    else
    {
        //parent
        close(p1[READ]);
        close(p2[WRITEE]);
        write(p1[WRITEE], send, 1);
        read(p2[READ], rec, 1);
        fprintf(1, "%d:received pong\n", getpid());
        close(p1[WRITEE]);
        close(p2[READ]);
        exit(0);
    }
}