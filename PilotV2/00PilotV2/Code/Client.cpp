// #include "stdafx.h" // " "
#include "Client.h"

Client::Client(void) {

	// WSADATA object // Stores win socket init info
	WSADATA wsaData;

	// socket
	ConnectSocket = INVALID_SOCKET;	

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	// error check
	if (iResult != 0) {
		printf("WSAStartup failed...\nError: %d\n", iResult);
		exit(1);
	}

	// Stores address info (for socket connection)
	struct addrinfo *result = NULL, *ptr = NULL, addr_info;
	ZeroMemory(&addr_info, sizeof(addr_info));
	addr_info.ai_family = AF_UNSPEC;		// IPV4 or IPV6
	addr_info.ai_socktype = SOCK_STREAM;	// TCP
	addr_info.ai_protocol = IPPROTO_TCP;	// TCP					  
									  
	//resolve server address and port
	// TO DO: potentially change this as it is currently set to localhost
	// *******************************************************************
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &addr_info, &result);
	// *******************************************************************

	// error check
	if (iResult != 0)
	{
		printf("getaddrinfo failed...\nError: %d\n", iResult);
		WSACleanup();
		exit(1);
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL;ptr = ptr->ai_next) 
	{
		// Create SOCKET for server connection
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		// error check
		if (ConnectSocket == INVALID_SOCKET) {
			printf("Socket failed...\nError: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		// error checking
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("Failed to establish connection...");
		}
	}

	// Server address info no longer necessary
	freeaddrinfo(result);

	// failed connection
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to the server!\n");
		WSACleanup();
		exit(1);
	}

	// put the socket into non-blocking mode.
	u_long iMode = 1;
	iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);

	// error check
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed...\nError: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}

	// disable nagle algorithm (can cause latency issues)
	char value = 1;
	setsockopt(ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

}