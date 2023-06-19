#ifndef CLIENT_H
# define CLIENT_H

void    exit_failure(int server_pid, int error);
void update_vals (int *bit, int *i);
void    exit_success(void);
void    char_to_bin(unsigned const c, int pid);
int check_pid(char *argv);

#endif