#include "ft_printf.h"
#include <signal.h>


void	action(int sig, siginfo_t *info, void *context)
{
    if (sig || context)
        ft_printf("");
    ft_printf("Client PID on server side %i\n", info->si_pid);
    kill(info->si_pid, SIGUSR2);
    ft_printf("I am waiting a bit lalalallalallala");
    //sleep(1);
    ft_printf("I just woke up\n");
    kill(info->si_pid, SIGUSR2);

    kill(info->si_pid, SIGUSR1);
    sleep(1);
    kill(info->si_pid, SIGUSR2);
    ft_printf("just sent a new signal to %i\n", info->si_pid);


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