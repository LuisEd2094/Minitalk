
#include "ft_printf.h"
#include "minitalk.h"
#include "server.h"
#include <signal.h>
#include <stdio.h>


t_server *g_server;

void    set_g_vals(void)
{
    g_server->buff_char = 0;
    g_server->client_pid = 0;
    g_server->working = 0;
    g_server->c = 0;
    g_server->i = 0;
    clear_buffer(g_server->buffer);
}

void work_on_signal(int sig, siginfo_t *info)
{
    handle_sig(sig, &(g_server->c));
    g_server->i++;
	if (g_server->i == 8)
	{
        g_server->i = 0;
        g_server->buffer[g_server->buff_char++] = g_server->c;
        if (g_server->buff_char == 10000 || g_server->c == '\0')
        {
            ft_printf("%s", g_server->buffer);
            if (g_server->c == '\0')
            {   
                str_done(info);
                return ; 
            }
            g_server->buff_char = 0;
            g_server->c = 0;
            clear_buffer(g_server->buffer);
        }
		g_server->c = 0;
	}
    usleep(10);
    if (send_signal(info->si_pid, SIGUSR1) != 1)
        if_failed(info);
}

void	action(int sig, siginfo_t *info, void *context)
{    
    (void)context;
    if (!g_server->client_pid)
        g_server->client_pid = info->si_pid;
    if (g_server->client_pid == info->si_pid && !g_server->working)
    {
        g_server->working = 1;
        if (send_signal(g_server->client_pid, SIGUSR1) != 1)
        {
            ft_printf("Error, couldn't send signal to %i.\n \
            Server is ready.", g_server->client_pid);
            set_g_vals();
        }
    }
    else if (g_server->client_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    else if (g_server->client_pid == info->si_pid && g_server->working)
        work_on_signal(sig, info);
}

void main_loop(void)
{
    while(1)
    {
        sleep(3);
        if (g_server->client_pid && \
        send_signal(g_server->client_pid, 0) != 1)
        {
            set_g_vals();
            ft_printf("Server is ready for a new client\n");
        }
    }
}

int main(void)
{
    int     pid;
    struct sigaction act;

    g_server = (t_server*)malloc(sizeof(t_server));
    if (g_server == NULL) {
        printf("Failed to allocate memory for g_server\n");
        return (1);
    }
    set_g_vals();
    pid = getpid();
    ft_printf("Server PID: %i\n", pid);
    act.sa_sigaction = action;
    if (sigemptyset(&act.sa_mask) == -1)
        perror("Error: "); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    main_loop();
    return(0);
}