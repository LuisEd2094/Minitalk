#include "ft_printf.h"
#include "libft.h"
#include <signal.h>


void new_action(int sig, siginfo_t *info, void *context)
{
    if (sig || info || context)
        ft_printf("");
    ft_printf("I got a signal to wake the fuck up \n");
}

void	action(int sig, siginfo_t *info, void *context)
{

    struct sigaction act;

    if (context || info)
        ft_printf("");
    if (sig == SIGUSR2)
    {
        ft_printf("I think I am changing my logic\n");
        act.sa_sigaction = new_action;
        sigaddset(&act.sa_mask, SIGUSR2); /// tis can throw error;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR2, &act, 0);
        ft_printf("I woke up\n");
        usleep(1);
    }
    else if (sig == SIGUSR1)
    {
        ft_printf("I got a signal from the server to wait \n");
        sleep(2);
    }
}
int main(int argc, char **argv)
{
    int server_pid = ft_atoi(argv[1]);

    struct sigaction act;

    act.sa_sigaction = action;
    sigemptyset(&act.sa_mask); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);

    if (argc == 1)
        return (1);
    ft_printf("Server PID on client side %i\n", server_pid);
    ft_printf("Client PID on Client %i\n", getpid());
    kill(server_pid, SIGUSR2);
    pause();
    
    return(0);
}