#ifndef SERVER_H
# define SERVER_H

typedef struct t_server_s
{
    char    c;
    char    buffer[10001];
    int     buff_char;
    int     client_pid;
    int     working;
    int     i;
} t_server;

#endif