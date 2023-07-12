/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:06:22 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/06/20 16:06:26 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minitalk.h"
#include "server.h"
#include <signal.h>
#include <stdio.h>

void	if_failed(siginfo_t *info)
{
	set_g_vals();
	ft_printf("Error, couldn't send signal to %i\
.\nServer is ready.", info->si_pid);
}

void	clear_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (i < 10001)
		buffer[i++] = 0;
}

void	handle_sig(int sig, char *c)
{
	if (sig == SIGUSR2)
		*c = *c << 1;
	else if (sig == SIGUSR1)
		*c = (*c << 1) | 0b00000001;
}

void	str_done(siginfo_t *info)
{
	getpid();
	set_g_vals();
	ft_printf("\nDone printing string from Client %i\nMy pid is: %i\n", \
			info->si_pid, getpid());
}

int	error_handle(int error)
{
	if (error == 1)
		ft_printf("Failed to set empty sig, exiting\n");
	else if (error == 2)
		ft_printf("Failed to allocate memory for g_server\n");
	else if (error == 3)
		ft_printf("Incorrect usage, just run ./server to start the server\n");
	else if (error == 4)
		ft_printf("Coulnd't set SIGUSR1, exiting\n");
	else if (error == 5)
		ft_printf("Coulnd't set SIGUSR2, exiting\n");
	exit (1);
}
