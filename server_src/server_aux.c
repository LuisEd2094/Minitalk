
#include "ft_printf.h"
#include "minitalk.h"
#include "server.h"
#include <signal.h>
#include <stdio.h>

void if_failed (siginfo_t *info)
{
    set_g_vals();
    ft_printf("Error, couldn't send signal to %i\
    .\nServer is ready.", info->si_pid);
}

void    clear_buffer(char *buffer)
{
    int i;
    
    i = 0;
    while (i < 10001)
        buffer[i++] = 0;
}

void    handle_sig (int sig, char *c)
{
    if (sig == SIGUSR2)
		*c = *c << 1;
	else if (sig == SIGUSR1)
		*c = (*c << 1) | 0b00000001;
}

void    str_done(siginfo_t *info)
{
    set_g_vals();
    ft_printf("\nDone printing string from Client %i\n",\
     info->si_pid);
}

int error_handle(int error)
{
    if (error == 1)
        ft_printf("Failed to set empty sig, exiting\n");
    else if (error == 2)
        ft_printf("Failed to allocate memory for g_server\n");
    exit (1);
}
