#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int new_socket, privilegeSet, valread;
    char *msg;
    char buffer[1024] = {0};
    if (argc > 1)
    {
        new_socket = *argv[1];
        msg = argv[2];
    }
    else
    {
        printf("Child Received in correct arguments");
        exit(0);
    }
    privilegeSet = setuid(65534);
    if (privilegeSet == -1)
    {
        printf("Reducing Privialge Failed\n");
        return 0;
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, msg, strlen(msg), 0);
    printf("Message sent\n");
    return 0;
}
