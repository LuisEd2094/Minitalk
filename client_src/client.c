#include "ft_printf.h"
#include "libft.h"
#include <signal.h>



void	char_to_bin(unsigned const c, int pid)
{
    static char i = 0;

    ft_printf("I am sending a bit i = %i\n", i);
	if (c << i & 0b10000000)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	i++;
    if (i == 8)
        i = 0;
}



void send_str(int sig, siginfo_t *info, void *context)
{
    char * str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam elementum tempus enim, ac dignissim tellus tincidunt in. Nunc rutrum ornare erat, non bibendum felis congue venenatis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Ut eleifend nunc sem, id suscipit ante faucibus id. Quisque vitae orci fringilla, gravida nulla ut, sollicitudin lectus. Curabitur sagittis velit ac sem condimentum, nec tincidunt ante sagittis. Integer sit amet fermentum ipsum, ut aliquam odio. Fusce vitae nulla pellentesque, sodales nibh malesuada, tincidunt enim. Fusce ligula est, tempor non nibh eget, auctor luctus eros. Mauris sem enim, dignissim at pretium.";
    static int i = 0;
    static int bit = 0;

    if (sig == SIGUSR1)
    {
        if (str[i])
        {
            if(sig || context)
            {
                sig = sig;
            }
            if (bit < 8)
            {
                char_to_bin(str[i], info->si_pid);
                bit++;

            }
            if (bit == 8)
            {
                bit = 0;
                i++;
            }
        }
    }

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