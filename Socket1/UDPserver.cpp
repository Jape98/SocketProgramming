#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 1;
	}

	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w); //tai 0x00020002 makewor:in tilalle

	if (ret != 0) {
		printf("Winsock API cannot be started \n");
		return 1;
	}

	printf("Winsock API ready \n");
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s == SOCKET_ERROR) {
		printf("Socket cannot be created");
		return 1;
	}

	SOCKADDR_IN la;
	la.sin_family = AF_INET;
	la.sin_port = htons(atoi(argv[1]));
	la.sin_addr.s_addr = INADDR_ANY;

	ret = bind(s, (SOCKADDR*)&la, sizeof(la));
	if (ret == SOCKET_ERROR) {
		return 1;
	}
	printf("UDP server ready on port %d\n", atoi(argv[1]));

	while (1) {
		char rbuf[100];
		memset(rbuf, 0, 100);
		ret = recvfrom(s, rbuf, 100, 0, NULL, NULL);
		if (ret > 0) {
			printf("Message: %s\n", rbuf);
		}
	}
}