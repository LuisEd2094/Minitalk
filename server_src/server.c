#include "ft_printf.h"
#include "minitalk.h"
#include "server.h"
#include <signal.h>
#include <stdio.h>

char buffer[10000];
t_server *g_server;

void    clear_buffer(void)
{
    int i;
    
    i = 0;
    while (i < 1001)
        g_server->buffer[i++] = 0;
}

int work_on_signal(int sig, siginfo_t *info)
{
	static int				i = 0;
    static int              buff_char = 0;

   // if (context)
        //ft_printf("");
    //context = "";
	if (sig == SIGUSR2)
		g_server->c = g_server->c << 1;
	else if (sig == SIGUSR1)
		g_server->c = (g_server->c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
        i = 0;
        g_server->buffer[buff_char++] = g_server->c;
        if (buff_char == 1000 || g_server->c == '\0')
        {
            ft_printf("%s", g_server->buffer);
            clear_buffer();
            buff_char = 0;
            if (g_server->c == '\0')
            {
                g_server->c = 0;
                buff_char = 0;
                ft_printf("\nDone printing string from Client %i\n", info->si_pid);
                return(0);
            }
            g_server->c = 0;
        }
		g_server->c = 0;
	}
    if (send_signal(info->si_pid, SIGUSR1) != 1)
    {
        ft_printf("Error, couldn't send signal to %i.\nServer is ready.", info->si_pid);
        return (0);
    }
    return (1);
}

void	action(int sig, siginfo_t *info, void *context)
{
    //static int current_pid = 0;
    //static int next_pid = 0;
    static int working_signal = 0;
    
    if (sig || context)
        ft_printf("");
    if (!g_server->client_pid)
        g_server->client_pid = info->si_pid;
    //else if (current_pid != info->si_pid)
        //next_pid = info->si_pid;
    if (g_server->client_pid == info->si_pid && working_signal)
        working_signal = work_on_signal(sig, info);
    else if (g_server->client_pid == info->si_pid && !working_signal)
    {
        working_signal = 1;
        if (send_signal(g_server->client_pid, SIGUSR1) != 1)
        {
            working_signal = 0;
            ft_printf("Error, couldn't send signal to %i.\nServer is ready.", g_server->client_pid);
            g_server->client_pid = 0;
        }
    }
    else if (g_server->client_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    /*if (!working_signal)
    {
        ft_printf("Sending confirmation to next\n");
    
        working_signal = 1;
        kill(current_pid, SIGUSR1);
    }*/
    if (!working_signal && g_server->client_pid)
        g_server->client_pid = 0;
}

int main(void)
{
    int     pid;
    struct sigaction act;
    g_server = (t_server*)malloc(sizeof(t_server));
    if (g_server == NULL) {
        printf("Failed to allocate memory for g_server\n");
        return 1;
    }
    g_server->client_pid = 0;
    g_server->c = 0;
    clear_buffer();
    pid = getpid();
    ft_printf("Server PID: %i\n", pid);
    act.sa_sigaction = action;
    if (sigemptyset(&act.sa_mask) == -1)
        perror("Error: "); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    while(1)
    {
        sleep(5);
        if (g_server->client_pid)
        {
            if (send_signal(g_server->client_pid, 0) != 1)
                exit(-1);
        }

    }
    return(0);
}