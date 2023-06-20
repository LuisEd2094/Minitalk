/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_signal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:00:39 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/06/20 16:00:40 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf.h"

int	send_signal(int pid, int sig)
{
	if (kill(pid, sig) != 0)
	{
		ft_printf("Error when sending signal to: %i\n", pid);
		return (-1);
	}
	return (1);
}
