#include <signal.h>
#include <stdio.h>

int send_signal(int sig, int pid)
{
    if (kill(pid, sig) == -1)
    {
        perror("Error\n");
        return (0);
    }
    return (1);
}
