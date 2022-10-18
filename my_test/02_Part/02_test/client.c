#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len = 0;
	int idx = 0, read_len = 0, i;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성
	//소켓을 생성하는 순간에는 서버 소켓과 클라이언트 소켓으로 나누어지지 않는다.
	//bind, listen 함수의 호출이 이어지면 서버 소켓이 되는 것이고, connect 함수의 호출로 이어지면 클라이언트 소켓이 되는 것이다
	if (sock == -1) error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));


	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) //connect 함수호출을 통해서 서버프로그램에 연결을 요청
		error_handling("connect() error!");

	/*
	   클라이언트가 read 함수의 호출 시기를 늦추는 이유
	   ->서버가 데이터를 모두 전송할 때까지 기다려야 하기 때문이다.
*/
	sleep(10000);
	for (i = 0; i<10000; i++)
		printf("Wait time %d \n", i);

	read(sock, message, sizeof(message)); //데이터의 경계가 존재하지 않으므로 한번에 다 수신 가능
	printf("Message from server: %s \n", message);
	close(sock);
	return 0;
}
void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
