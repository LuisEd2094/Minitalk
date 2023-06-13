#include <signal.h>
#include "ft_printf.h"

int send_signal(int pid, int sig)
{
    if (kill(pid, sig) != 0)
    {
        ft_printf("Error when sending signal to: %i\n", pid);
        return (-1);
    }
    return (1);
}
