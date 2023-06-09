#include "ft_printf.h"
#include <signal.h>


void	action(int sig, siginfo_t *info, void *context)
{
    static int current_pid = 0;
    static int nex_pid = 0;
    static int counter = 0;
    
    if (sig || context)
        ft_printf("");
    if (!current_pid)
        current_pid = info->si_pid;
    else if (current_pid != info->si_pid)
        nex_pid = info->si_pid;
    ft_printf("Current %i Next %i\n", current_pid, nex_pid);    
    if (current_pid == info->si_pid && counter < 10000)
    {
        counter++;
        ft_printf("I am sending a confirmation signal\nCounter = %i", counter);
        kill(current_pid, SIGUSR1);
    }
    else if (current_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    if (counter >= 10000 && nex_pid)
    {
        ft_printf("I am switching clients to serve\n");
        ft_printf("Current %i Next %i\n", current_pid, nex_pid);
        current_pid = nex_pid;
        ft_printf("After change Current %i Next %i\n", current_pid, nex_pid);

        counter = 0;
        kill(current_pid, SIGUSR1);
    }
}

int main(void)
{
    int     pid;
    struct sigaction act;

    pid = getpid();
    ft_printf("%i\n", pid);
    act.sa_sigaction = action;
    sigemptyset(&act.sa_mask); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    ft_printf("Soy el Server\n");

    while (1)
        pause();
    return(0);
}