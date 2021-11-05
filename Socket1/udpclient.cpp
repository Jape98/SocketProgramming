#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "sw2_32.lib")



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

}