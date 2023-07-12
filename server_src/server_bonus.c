/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:04:46 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/07/07 10:09:32 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minitalk_bonus.h"
#include "server_bonus.h"
#include <signal.h>
#include <stdio.h>

t_server	*g_server;

void	set_g_vals(void)
{
	g_server->buff_char = 0;
	g_server->client_pid = 0;
	g_server->working = 0;
	g_server->c = 0;
	g_server->i = 0;
	clear_buffer(g_server->buffer);
}

void	work_on_signal(int sig, siginfo_t *info)
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
	usleep(50);
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

void	main_loop(void)
{
	int		pid;

	pid = getpid();
	ft_printf("Server PID: %i\n", pid);
	while (1)
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

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	if (argc != 1 && argv)
		error_handle(3);
	g_server = (t_server *)malloc(sizeof(t_server));
	if (g_server == NULL)
		error_handle(2);
	set_g_vals();
	act.sa_sigaction = action;
	if (sigemptyset(&act.sa_mask) == -1)
		error_handle(1);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		error_handle(4);
	if (sigaction(SIGUSR2, &act, 0) == -1)
		error_handle(5);
	main_loop();
	return (0);
}
