#include "ft_printf.h"
#include "minitalk.h"
#include <signal.h>
#include <stdio.h>

char buffer[10000];

void    clear_buffer(void)
{
    int i;
    
    i = 0;
    while (buffer[i])
        buffer[i++] = 0;
}

int work_on_signal(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
    static int              buff_char = 0;
	static unsigned char	c = 0;

	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
        i = 0;
        buffer[buff_char++] = c;
        if (buff_char == 10000 || c == '\0')
        {
            ft_printf("%s", buffer);
            clear_buffer();
            buff_char = 0;
            if (c == '\0')
            {
                c = 0;
                buff_char = 0;
                ft_printf("\nDone printing string from Client %i\n", info->si_pid);
                return (0);
            }
            c = 0;
        }
		c = 0;
	}
    if (send_signal(info->si_pid, SIGUSR1) != 1)
    {
        ft_printf("Error, couldn't send signal to %i.\nServer is ready.", info->si_pid);
        return (0);
    }
    return (1);
}
/*
void	action(int sig, siginfo_t *info, void *context)
{
    static int current_pid = 0;
    //static int next_pid = 0;
    static int working_signal = 0;
    
    if (sig || context)
        ft_printf("");
    if (!current_pid)
        current_pid = info->si_pid;
    //else if (current_pid != info->si_pid)
        //next_pid = info->si_pid;
    if (current_pid == info->si_pid && working_signal)
        working_signal = work_on_signal(sig, info);
    else if (current_pid == info->si_pid && !working_signal)
    {
        working_signal = 1;
        if (send_signal(current_pid, SIGUSR1) != 1)
        {
            working_signal = 0;
            ft_printf("Error, couldn't send signal to %i.\nServer is ready.", current_pid);
            current_pid = 0;
        }
    }
    else if (current_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    /*if (!working_signal && next_pid)
    {
        ft_printf("Sending confirmation to next\n");
        current_pid = next_pid;
        next_pid = 0;        
        working_signal = 1;
        kill(current_pid, SIGUSR1);
    }*//*
    if (!working_signal && current_pid)
        current_pid = 0;
}*/

int main(void)
{
    int     pid;
    struct sigaction act;

    pid = getpid();
    ft_printf("Server PID: %i\n", pid);
    act.sa_sigaction = work_on_signal;
    if (sigemptyset(&act.sa_mask) == -1)
        perror("Error: "); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    while (1)
        pause();
    return(0);
}