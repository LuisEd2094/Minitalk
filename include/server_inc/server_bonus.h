#ifndef SERVER_H
# define SERVER_H
# include <signal.h>

typedef struct t_server_s
{
    char    c;
    char    buffer[10001];
    int     buff_char;
    int     client_pid;
    int     working;
    int     i;
} t_server;


void    clear_buffer(char *buffer);
void    if_failed (siginfo_t *info);
void    set_g_vals(void);
void    handle_sig (int sig, char *c);
void    str_done(siginfo_t * info);
int     error_handle(int error);
#endif