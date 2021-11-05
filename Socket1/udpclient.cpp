#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[]) {
	
	if (argc != 3) { //command "ip" "port"

		printf("Help: %s [IP] [Port]\n", argv[0]);
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

	// prepare remote(server) address, sa
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(argv[1]);
	sa.sin_port = htons(atoi(argv[2]));
	printf("Udp client ready to go");

	while(true) {

		char sbuf[100];
		printf("Message here >>");
		fgets(sbuf, 100, stdin); //buffer,size and input
		// socket to use, how many bytes to send out, flag = 0, remote address created earlier, size of my remote address.
		ret = sendto(s, sbuf, strlen(sbuf),0,(SOCKADDR *)&sa,sizeof(sa));

		if (ret == SOCKET_ERROR) {
			printf("Sendto failed\n");
			break;
		}
	}
}