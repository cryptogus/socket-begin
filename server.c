#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv){

    int server_sock;
    int client_sock;
    int client_addr_size;
    char message[] = "Hello World\n";

    struct sockaddr_in serv_addr;
    
    server_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    bind(server_sock,(struct sockaddr*) &serv_addr, sizeof(serv_addr) );
    listen(server_sock,5);
    
    client_addr_size = sizeof(client_addr_size);
    client_sock = accept(server_sock, (struct sockaddr*) &client_sock, &client_addr_size);
    write(client_sock, message, sizeof(message));
    close(client_sock);

    return 0;
}