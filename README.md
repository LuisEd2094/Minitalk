# Minitalk

Minitalk Project from 42 School

It's an introduction to Signals, we have two programs Server and Client.

Run Make to create the necessary files. There is special bonus rule in the make file since the project does include part of the bonus for the evaluation,
but it's the same code. Since the Subject states we need to present the bonus in different files, I had to do it this way. Bonus part is that Server 
sends a "ready" signal to the client before the client sends the next bit. Since we need this signal for the normal operations, both programs will run
the same way.

First we need to start Server to get it's PID and then we can run Client <Server PID> <String to print>.

Client will check if the PID provided correspond to the server, for which the Server will send an acknowledgement. Once Client receives the signal,
Client will send each character from the string in the form of SIGUSR1 and SIGUSR2, the Server will interpret them as 0's and 1's, reconstructing the 
string bit by bit.

Once Server receives '\0' or his 10001 buffer is full, it'd print the string and either continue receiving the next bits or it'd get ready to get a new
string from a new client.

If a second Client tries to send a string while the Server is busy with another Client, the second Client will receive a negative from the Server and 
the second Client will close, you will need to try again once the Server is ready, although there is no queue mechanism.

