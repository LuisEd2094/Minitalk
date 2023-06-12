#include "ft_printf.h"
#include <signal.h>


int work_on_signal(int sig, siginfo_t *info)
{
	static int				i = 0;
	static unsigned char	c = 0;

	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
        if (c == '\0')
        {
            c = 0;
            ft_printf("\nDone printing string from %i\n", info->si_pid);
            return (0);
        }
		c = 0;
	}
    kill(info->si_pid, SIGUSR1);
    return (1);
}

void	action(int sig, siginfo_t *info, void *context)
{
    static int current_pid = 0;
    static int next_pid = 0;
    static int working_signal = 0;
    
    if (sig || context)
        ft_printf("");
    if (!current_pid)
        current_pid = info->si_pid;
    else if (current_pid != info->si_pid)
        next_pid = info->si_pid;
    if (current_pid == info->si_pid && working_signal)
        working_signal = work_on_signal(sig, info);
    else if (current_pid == info->si_pid && !working_signal)
    {
        working_signal = 1;
        kill(current_pid, SIGUSR1);
    }
    else if (current_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    if (!working_signal && next_pid)
    {
        ft_printf("Sending confirmation to next\n");
        current_pid = next_pid;
        next_pid = 0;        
        working_signal = 1;
        usleep(100);
        kill(current_pid, SIGUSR1);
    }
    else if (!working_signal && current_pid)
        current_pid = 0;
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
    while (1)
        pause();
    return(0);
}