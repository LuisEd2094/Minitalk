#ifndef SERVER_H
# define SERVER_H

typedef struct t_server_s
{
    char    c;
    char    buffer[1001];
    int     client_pid;
} t_server;

#endif