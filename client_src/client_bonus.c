#include "ft_printf.h"
#include "libft.h"
#include "minitalk.h"
#include "client.h"
#include <signal.h>
#include <errno.h>
#include <stdio.h>

char *g_str;


void	char_to_bin(unsigned const c, int pid)
{
    static char i = 0;
    int sig;

	if (c << i & 0b10000000)
		sig = send_signal(pid, SIGUSR1);
	else
		sig = send_signal(pid, SIGUSR2);
    if (sig != 1)
        exit_failure(0, 4);
    if (++i == 8)
        i = 0;
}

void send_str(int sig, siginfo_t *info, void *contex)
{
    static int i = 0;
    static int bit = 0;

    if (contex)
        ft_printf("");
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
            {
                ft_printf("Done printing string, exiting\n");
                exit(0);
            }
        }        
    }

}

void	action(int sig, siginfo_t *info, void *context)
{
    struct sigaction act;

    if (context || info)
        ft_printf("");
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
        ft_printf("Server not ready, try again later\n");
        exit (0);
    }

}

int check_pid(char *argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        if (!ft_isdigit(argv[i++]))
            exit_failure(0, 2);
    }
    return (ft_atoi(argv));
}

int main(int argc, char **argv)
{
    int server_pid ;
    struct sigaction act;

    ft_printf("Client PID %i\n", getpid());
    if (argc != 3)
        exit_failure(0, 3);
    server_pid = check_pid(argv[1]);
    g_str = argv[2];
    act.sa_sigaction = action;
    if (sigemptyset(&act.sa_mask) == -1)
        perror("Error: ");  /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    if (send_signal(server_pid, SIGUSR1) != 1)
        exit_failure(server_pid, 1);
    while(1)
    {
        sleep(5);
        if (send_signal(server_pid, 0) != 1)
            exit_failure(server_pid, 5);
    }

}