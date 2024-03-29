/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:59:36 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/07/05 11:39:21 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minitalk_bonus.h"
#include "client_bonus.h"
#include <signal.h>
#include <errno.h>
#include <stdio.h>

char	*g_str;

void	send_str(int sig, siginfo_t *info, void *contex)
{
	static int	i = 0;
	static int	bit = 0;

	(void)contex;
	usleep(50);
	if (sig == SIGUSR1)
	{
		if (g_str[i])
		{
			if (bit++ < 8)
				char_to_bin(g_str[i], info->si_pid);
			if (bit == 8)
				update_vals(&bit, &i);
		}
		else if (!g_str[i])
		{
			if (bit++ < 8)
				char_to_bin(g_str[i], info->si_pid);
			if (bit == 8)
				exit_success();
		}
	}
}

void	action(int sig, siginfo_t *info, void *context)
{
	struct sigaction	act;

	(void)context;
	if (sig == SIGUSR1)
	{
		ft_printf("Server ready! Sending message!\n");
		act.sa_sigaction = send_str;
		if (sigaddset(&act.sa_mask, SIGUSR1) == -1)
			exit_failure(0, 8);
		act.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &act, 0) == -1)
			exit_failure(0, 8);
		send_str(sig, info, context);
	}
	else if (sig == SIGUSR2)
		exit_failure(0, 7);
}

void	main_loop(int server_pid)
{
	while (1)
	{
		sleep(3);
		if (send_signal(server_pid, 0) != 1)
			exit_failure(server_pid, 5);
	}
}

int	main(int argc, char **argv)
{
	int					server_pid ;
	struct sigaction	act;

	if (argc != 3 || !argv[1][0] || argv[1][0] == '0' || !argv[2][0])
		exit_failure(0, 3);
	ft_printf("Client PID %i\n", getpid());
	server_pid = check_pid(argv[1]);
	g_str = argv[2];
	act.sa_sigaction = action;
	if (sigemptyset(&act.sa_mask) == -1)
		exit_failure(0, 6);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		exit_failure(0, 8);
	if (sigaction(SIGUSR2, &act, 0) == -1)
		exit_failure(0, 9);
	if (send_signal(server_pid, SIGUSR1) != 1)
		exit_failure(server_pid, 1);
	main_loop(server_pid);
	return (0);
}
