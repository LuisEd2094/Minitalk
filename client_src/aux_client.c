#include "ft_printf.h"
#include <stdlib.h>

void    exit_failure(int server_pid, int error)
{
    if (error == 1)
        ft_printf("Couldn't send sig to %i, exiting\n", server_pid);
    else if (error == 2)
        ft_printf("Invalid argument value for PID, please introduce server's PID\n");
    else if (error == 3)
        ft_printf("Inorrect use. Run ./server, get server PID, run \
        ./client <server PID> <String to print>\n");
    else if (error == 4)
        ft_printf("Exiting after failing to send signal to server.\n");
    else if (error == 5)
        ft_printf("Server %i is no longer reachable, exiting!\n", server_pid);
    exit(0);
}