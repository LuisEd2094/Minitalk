#include "ft_printf.h"
#include "libft.h"
#include <signal.h>



void	char_to_bin(unsigned const c, int pid)
{
    static char i = 0;

	if (c << i & 0b10000000)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	i++;
    if (i == 8)
        i = 0;
}



void send_str(int sig, siginfo_t *info, void *context)
{
    char * str = "Donec sit amet lacinia nulla. Phasellus auctor metus sed lorem pretium, quis rhoncus odio vehicula. Maecenas bibendum sapien quis enim convallis, vitae laoreet metus venenatis. Suspendisse ut turpis eget ligula tempus pulvinar. Vestibulum molestie ipsum ante, ac iaculis nibh fermentum sit amet. Integer auctor, urna eget egestas laoreet, sapien urna pharetra massa, sagittis imperdiet metus nulla sit amet ligula. Aenean nec tincidunt nisl. Curabitur sollicitudin, mauris nec accumsan ultricies, libero nunc feugiat est, quis accumsan nisl enim eget eros. Sed eget dui vulputate, vestibulum odio sit amet, viverra risus. Mauris nec ornare felis, non egestas erat. Vestibulum ut orci auctor, scelerisque erat non, pellentesque dui. Nam pharetra ornare risus et euismod. Donec blandit. Sed rutrum vulputate pulvinar. Vivamus efficitur scelerisque condimentum. Nunc sed molestie magna. Proin ligula mauris, volutpat maximus magna quis, gravida porttitor dui. Nam nec nibh at nibh dictum facilisis nec non leo. Donec venenatis eros vitae lectus consectetur sodales. Curabitur quis facilisis leo. Nam cursus sapien id porta pretium. Maecenas tellus mauris, tristique et lectus eu, egestas interdum tortor. Aenean feugiat dolor at orci dignissim pharetra. Suspendisse imperdiet risus sem, non rutrum lorem vulputate vel. Proin maximus mauris in justo lacinia varius. Fusce non augue non nibh bibendum eleifend. Suspendisse dui nisl, hendrerit ut aliquet non, iaculis et dui. Proin arcu ligula, vestibulum sit amet vulputate vitae, tempus eu mi. In malesuada est in sapien malesuada placerat. Nunc convallis non eros ut fringilla. Phasellus ut sapien in quam gravida interdum quis sed odio. Phasellus et augue vitae urna vulputate finibus sed eget tortor. Ut ultrices sem id venenatis consequat. Aliquam erat volutpat. Suspendisse potenti. Pellentesque laoreet justo non tellus fringilla, in tempor turpis dictum. Suspendisse in volutpat nulla. Nam finibus arcu felis. Nullam id metus orci. Etiam bibendum, nisi mollis bibendum auctor, felis erat vulputate felis, vitae venenatis neque risus a ligula. Quisque semper felis iaculis lacus elementum, eu commodo nulla laoreet. Nulla ultricies, erat eu porta interdum, tellus leo gravida lorem, vel finibus tellus urna sed leo. Proin vel feugiat metus. Etiam sit amet magna convallis, scelerisque leo sit amet, mattis mauris. Donec consequat, eros eu dictum sagittis, lorem lectus feugiat orci, eu iaculis est purus porta nisl. Fusce consectetur in neque at gravida. Praesent pellentesque velit maximus suscipit aliquam. Pellentesque eleifend faucibus velit. Aliquam ex nulla, aliquet in arcu ac, accumsan blandit diam. Curabitur dignissim erat id blandit imperdiet. Pellentesque vel iaculis augue. Nam tristique consequat tempus. Praesent eu arcu hendrerit, cursus justo vel, fringilla tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur placerat erat nec lacus gravida, in dapibus velit maximus. Quisque iaculis mauris neque, quis varius eros sodales vitae. Praesent nec auctor nisl. In nisi erat, vehicula in sollicitudin eu, cursus quis diam. Nullam ultrices, diam sit amet venenatis commodo, diam velit venenatis dui, tempus dignissim ante augue a mi. Duis et blandit mi. Maecenas bibendum varius vulputate. Nulla lectus metus, posuere nec neque quis, scelerisque iaculis enim. Donec non luctus lacus, vitae porta nisl. Praesent fermentum sed augue eu sollicitudin.";
    static int i = 0;
    static int bit = 0;

    if (sig == SIGUSR1)
    {
        if (str[i])
        {
            if(sig || context)
            {
                sig = sig;
            }
            if (bit < 8)
            {
                char_to_bin(str[i], info->si_pid);
                bit++;

            }
            if (bit == 8)
            {
                bit = 0;
                i++;
            }
        }
        
    }

}

void	action(int sig, siginfo_t *info, void *context)
{

    struct sigaction act;

    if (context || info)
        ft_printf("", SIGUSR2, SIGUSR1);
    if (sig == SIGUSR1) // valid signal
    {
        ft_printf("Server ready! Sending message!\n");
        act.sa_sigaction = send_str; // printer?
        sigaddset(&act.sa_mask, SIGUSR1); /// tis can throw error;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, 0);
        send_str(sig, info, context);
    }
    else if (sig == SIGUSR2)
    {
        ft_printf("Waiting for server to be ready\n");
    }
}
int main(int argc, char **argv)
{
    int server_pid = ft_atoi(argv[1]);
    struct sigaction act;

    act.sa_sigaction = action;
    sigemptyset(&act.sa_mask); /// tis can throw error;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, 0);
    sigaction(SIGUSR2, &act, 0);
    if (argc == 1)
        return (1);
    ft_printf("Server PID on client side %i\n", server_pid);
    ft_printf("Client PID on Client %i\n", getpid());
    kill(server_pid, SIGUSR1);
    while(1)
    {
        pause();
    }

    
    return(0);
}