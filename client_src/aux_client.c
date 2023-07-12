/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:51:58 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/06/19 17:53:42 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minitalk.h"
#include "client.h"
#include <signal.h>
#include <errno.h>
#include <stdio.h>

void	exit_failure(int server_pid, int error)
{
	if (error == 1)
		ft_printf("Couldn't send sig to %i, exiting\n", server_pid);
	else if (error == 2)
		ft_printf("Invalid argument value for PID, \
please introduce server's PID\n");
	else if (error == 3)
		ft_printf("Incorrect use. Run ./server_bonus first to get server PID. Run \
./client_bonus <server PID> <String to print>\n");
	else if (error == 4)
		ft_printf("Exiting after failing to send signal to server.\n");
	else if (error == 5)
		ft_printf("Server %i is no longer reachable, exiting!\n", server_pid);
	else if (error == 6)
		ft_printf("Failed to set empty sig, exiting\n");
	else if (error == 7)
		ft_printf("Server not ready, try again later\n");
	else if (error == 8)
		ft_printf("Couldn't set SIGUSR1, exiting\n");
	else if (error == 9)
		ft_printf("Couldn't set SIGUSR2, exiting\n");
	exit(0);
}

void	exit_success(void)
{
	ft_printf("Done printing string, exiting\n");
	exit(0);
}

void	update_vals(int *bit, int *i)
{
	*bit = 0;
	*i += 1;
}

void	char_to_bin(unsigned const char c, int pid)
{
	static char	i = 0;
	int			sig;

	if (c << i & 0b10000000)
		sig = send_signal(pid, SIGUSR1);
	else
		sig = send_signal(pid, SIGUSR2);
	if (sig != 1)
		exit_failure(0, 4);
	if (++i == 8)
		i = 0;
}

int	check_pid(char	*argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i++]))
			exit_failure(0, 2);
	}
	return (ft_atoi(argv));
}
