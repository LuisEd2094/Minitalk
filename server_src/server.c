#include "ft_printf.h"
#include <signal.h>


void work_on_signal(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

    info = info;
    context = context;
	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
    kill(info->si_pid, SIGUSR1);
}

void	action(int sig, siginfo_t *info, void *context)
{
    static int current_pid = 0;
    static int nex_pid = 0;
    static int working_signal = 0;
    
    if (sig || context)
        ft_printf("");
    if (!current_pid)
        current_pid = info->si_pid;
    else if (current_pid != info->si_pid)
        nex_pid = info->si_pid;
    if (current_pid == info->si_pid && working_signal)
        work_on_signal(sig, info, context);
    else if (current_pid == info->si_pid && !working_signal)
    {
        working_signal = 1;
        kill(current_pid, SIGUSR1);
    }
    else if (current_pid != info->si_pid)
        kill(info->si_pid, SIGUSR2);
    if (nex_pid)
        nex_pid = nex_pid;
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