#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char *argv[]) {

	if (argc != 3) { 

		printf("Help: %s [IP] [Port]\n", argv[0]);
		return 1;
	}

	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w); //tai 0x00020002 makeword:in tilalle

	if (ret != 0) {
		printf("Winsock API cannot be started \n");
		return 1;
	}

	printf("Winsock API ready \n");
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	if (s == SOCKET_ERROR) {
		printf("Socket cannot be created");
		return 1;
	}

	// prepare remote(server) address, sa
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(argv[1]);
	sa.sin_port = htons(atoi(argv[2])); //htons() host to network address, atoi() string to int
	ret = connect(s, (SOCKADDR*)&sa, sizeof(sa));

	if (ret == SOCKET_ERROR) { // ímportant
		printf("Connection failed, please check your internet");
		return 1;
	}

	printf("Server %s is connected\n", argv[1]);

	while (1) {
		char sbuf[100];
		printf("Message >> ");
		fgets(sbuf, 100, stdin);
		ret = send(s, sbuf, strlen(sbuf), 0);
		ret = recv(s, sbuf, 100, 0);

		if (ret > 0) {
			printf("Server :: %s\n", sbuf);
		}
	}

	closesocket(s); //destroy the socket
	WSACleanup();	//stop Winsock API
}