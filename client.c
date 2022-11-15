#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv){

    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    str_len = read(sock, message, sizeof(message));
    message[str_len] = 0;
    printf("Message from server : %s \n", message);

    return 0;
}