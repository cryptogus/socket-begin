//gcc server.c -o server
//./server [포트번호]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>

#define BUFSIZE 512

void run(struct sockaddr_in addr, int sock){
		
		// 접속한 클라이언트 정보 출력
		char temp[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, temp, sizeof(temp));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			temp, ntohs(addr.sin_port));

		char buf[BUFSIZE + 1];

		// 클라이언트와 데이터 통신
		while (1) {
			// 데이터 받기
			int	retval = recv(sock, buf, BUFSIZE, 0);
			
			if (retval == 0 || retval == -1)
				break;

			// 받은 데이터 출력
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", temp, ntohs(addr.sin_port), buf);

			// 데이터 보내기
			retval = send(sock, buf, retval, 0);

		}

		// 소켓 닫기
		close(sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			temp, ntohs(addr.sin_port));
}

int main(int argc, char *argv[]){

    int retval;

	// 소켓 생성
	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(atoi(argv[1]));
	retval = bind(listen_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	// listen()
	retval = listen(listen_sock, SOMAXCONN);

	// 데이터 통신에 사용할 변수
	int client_sock;
	struct sockaddr_in clientaddr;
	socklen_t addrlen;
	

	while(1){
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &addrlen);
		if(client_sock == -1){
			break;
		}
		new std::thread(&run, clientaddr, client_sock);
	}

	// 소켓 닫기
	close(listen_sock);
	return 0;
}