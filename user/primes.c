#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITEE 1
void child(int *pl);
int main(int argc, char *argv[])
{
    int fdp[2];
    pipe(fdp);
    int pid = fork();
    if (pid > 0)
    {
        // parent
        close(fdp[READ]);
        for (int i = 2; i <= 35; i++)
        {
            write(fdp[WRITEE], &i, sizeof(int));
        }
        close(fdp[WRITEE]);
        wait(0);
    }
    else
    {
        // child
        child(fdp);
    }
    exit(0);
}

void child(int *pl)
{
    int pr[2];
    int rec, n;
    close(pl[WRITEE]);
    int rd = read(pl[READ], &n, sizeof(int));
    if (rd == 0)
    {
        close(pl[READ]);
        exit(0);
    }
    fprintf(1, "prime: %d\n", n);
    pipe(pr);
    if (fork() == 0)
    {
        child(pr);
    }
    else
    {
        close(pr[READ]);
        while (read(pl[READ], &rec, sizeof(int)))
        {
            if (rec % n != 0)
                write(pr[WRITEE], &rec, sizeof(int));
        }
        close(pl[READ]);
        close(pr[WRITEE]);
        wait(0);
    }
    exit(0);
}