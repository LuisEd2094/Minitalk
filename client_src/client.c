#include "ft_printf.h"
#include "libft.h"
#include <signal.h>


void send_str(int sig, siginfo_t *info, void *context)
{
    if (sig || info || context)
        ft_printf("");
    if (sig == SIGUSR1)
        ft_printf("Here I am sending the signal\n");
    kill(info->si_pid, SIGUSR1);
}

void	action(int sig, siginfo_t *info, void *context)
{

    struct sigaction act;

    if (context || info)
        ft_printf("THIS IS SIG 2 %i, THIS IS SIG 1 %i\n", SIGUSR2, SIGUSR1);
    if (sig == SIGUSR1) // valid signal
    {
        ft_printf("Server ready! Sending message!\n");
        act.sa_sigaction = send_str; // printer?
        sigaddset(&act.sa_mask, SIGUSR1); /// tis can throw error;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, 0);
        send_str(sig, info, context);
    }
    else if (sig == SIGUSR2)
    {
        ft_printf("Waiting for server to be ready\n");
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
    kill(server_pid, SIGUSR1);
    while(1)
    {
        ft_printf("I left the handler\n");
        pause();
    }

    
    return(0);
}