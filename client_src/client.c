#include "ft_printf.h"
#include "libft.h"
#include <signal.h>
#include <errno.h>
#include <stdio.h>

char *g_str;

void send_signal(int sig, int pid)
{
    if (kill(pid, sig) == -1)
       {
        ft_printf("Error\n");
        perror(NULL);
        exit(EXIT_FAILURE);
       }
}

void	char_to_bin(unsigned const c, int pid)
{
    static char i = 0;

	if (c << i & 0b10000000)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
    if (++i == 8)
        i = 0;
}



void send_str(int sig, siginfo_t *info, void *contex)
{
    static int i = 0;
    static int bit = 0;

    if (contex)
        contex = contex;
    usleep(10);
    if (sig == SIGUSR1)
    {
        if (g_str[i])
        {
            if (bit++ < 8)
            {
                char_to_bin(g_str[i], info->si_pid);
            }
            if (bit == 8)
            {
                bit = 0;
                i++;
            }
        }
        else if(!g_str[i])
        {
            if (bit++ < 8)
                char_to_bin(g_str[i], info->si_pid);
            if (bit == 8)
                exit(0);
        }        
    }

}

void	action(int sig, siginfo_t *info, void *context)
{
    struct sigaction act;

    if (context || info)
        ft_printf("", SIGUSR2, SIGUSR1);
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
        ft_printf("Waiting for server to be ready\n");
}

int main(int argc, char **argv)
{
    int server_pid ;
    struct sigaction act;

    if (argc != 3)
        exit (-1);
    server_pid = ft_atoi(argv[1]);
    g_str = argv[2];
    act.sa_sigaction = action;
    sigemptyset(&act.sa_mask); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    ft_printf("Client PID on Client %i\n", getpid());
    kill(server_pid, SIGUSR1);
    while(1)
        pause();
    exit(0);
}