#include "kernel/types.h"
#include "user/user.h"

#define MAX_LEN 100

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: xargs command ...\n");
        exit(1);
    }
    int pid, rd, buf_index;
    char temp, *cmd[MAX_LEN], buf[MAX_LEN];
    for (int i = 1; i < argc; i++)
    {
        cmd[i - 1] = argv[i];
    }
    buf_index = 0;
    while ((rd = read(0, &temp, 1)) > 0)
    {
        if (temp == '\n')
        {
            buf[buf_index] = 0;
            pid = fork();
            if (pid < 0)
            {
                fprintf(2, "fork error");
                exit(1);
            }
            if (pid == 0)//child
            {
                cmd[argc - 1] = buf;
                cmd[argc] = 0;
                exec(cmd[0], cmd);
            }
            else//parent
            {
                wait(0);
                buf_index = 0;
            }
        }
        else
            buf[buf_index++] = temp;
    }
    exit(0);
}