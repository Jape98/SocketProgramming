#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Help: %s [port]\n", argv[0]);
		return 1;
	}

	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w); //or 0x00020002 isntead of makeword

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
		printf("Binding failed");
		return 1;
	}
	printf("UDP server ready on port %d\n", atoi(argv[1]));

	while (1) {
		char rbuf[100];
		memset(rbuf, 0, 100);

		SOCKADDR_IN	ra; //remote (client) socket address
		int fromlen = sizeof(ra);
		ret = recvfrom(s, rbuf, 100, 0, (SOCKADDR *)&ra, &fromlen);

		if (ret > 0) {
			printf("Message:(%s:%d): %s\n", inet_ntoa(ra.sin_addr),ntohs(ra.sin_port), rbuf); //inet_ntoa() address tó string, ntohs() network order to host order
			sprintf(rbuf, "You sent me %d bytes.", ret);
			sendto(s, rbuf, strlen(rbuf),0,(SOCKADDR*)&ra, sizeof(ra));
		}
	}
}