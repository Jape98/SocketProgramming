#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

// get hostbyname has to be used in most client programs, beacaise the user usually uses hostname instead of ip address.

int main(void){

	WSADATA w;
	int ret = WSAStartup(0x00020002, &w);

	if (ret != 0) {
		printf("Winsock API cannot start \n");
		return 1;
	}
	printf("I'm going to translate hostname into IP address \n");

	while (1) {
		printf("Hostname >> ");
		char hname[100]="\0";

		scanf("%s",hname);

		if (strcmp(hname, "EXIT") == 0) break;

		LPHOSTENT lph = gethostbyname(hname);
		SOCKADDR_IN sa;
		sa.sin_addr = *((LPIN_ADDR)*lph->h_addr_list);
		printf("%s has IP address as %s\n", hname, inet_ntoa(sa.sin_addr));
	}
}