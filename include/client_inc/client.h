/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:08:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/06/20 16:08:16 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

void	exit_failure(int server_pid, int error);
void	update_vals(int *bit, int *i);
void	exit_success(void);
void	char_to_bin(unsigned const char c, int pid);
int		check_pid(char *argv);

#endif
