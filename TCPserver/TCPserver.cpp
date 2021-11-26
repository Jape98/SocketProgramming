#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Help: %s [Port]\n", argv[0]);
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

	// prepare server(local) address, sa
	SOCKADDR_IN sa, ca; //sa = socket address, ca = client address
	sa.sin_family = AF_INET;
	sa.sin_port = htons(atoi(argv[1]));
	sa.sin_addr.s_addr = INADDR_ANY;

	ret = bind(s, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR) {
		printf("Bind failed, please check the port \n");
		return 1;
	}

	ret = listen(s, 5); // socket to listen and how many clients to handle.
	printf("Server is listening\n");
	if (ret == SOCKET_ERROR) {
		printf("asdf \n");
		return 1;
	}

	while (1) {
		int calen = sizeof(ca); //client address length
		SOCKET cs = SOCKET_ERROR;
		while (cs == SOCKET_ERROR) cs = accept(s, (SOCKADDR*)&ca, &calen);
		printf("A client from %s:%d comes in\n",inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));
		//now we can communicate with a client, if this is a wrong guy;

		char sbuf[100] = "This is not the right guy you can play with\r\n";
		for (int i = 0; i < 100; i++) {
			ret = send(cs, sbuf, strlen(sbuf), 0);
		}
		closesocket(cs);
	}



}
