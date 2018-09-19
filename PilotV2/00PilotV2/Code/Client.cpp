#include "Client.h"
#include <iostream>

using namespace std;

// constructor
Client::Client() 
{
	// Messy process with windows networking - "start" the networking API.
	WSADATA wsaData; // Stores win socket init info
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Stores address info (for socket connection)
	// TO DO: Discuss ai vs sin and what we want to use...
	// **********************************************************
	struct addrinfo *addr_result = NULL, *sock = NULL, addr_info;
	ZeroMemory(&addr_info, sizeof(addr_info));
	addr_info.ai_family = AF_UNSPEC;		// IPV4 or IPV6
	addr_info.ai_socktype = SOCK_STREAM;	// TCP
	addr_info.ai_protocol = IPPROTO_TCP;	// TCP		
	// **********************************************************
									  
	//resolve server address and port
	// TO DO: potentially change this as it is currently set to localhost
	// *******************************************************************
	getaddrinfo("127.0.0.1", DEFAULT_PORT, &addr_info, &addr_result);
	// *******************************************************************

	// Attempt connection
	for (sock = addr_result; sock != NULL; sock = sock->ai_next) 
	{
		// Socket
		socket_d = socket(sock->ai_family, sock->ai_socktype, sock->ai_protocol);

		// Connect
		// try connecting to server
		if (connect(socket_d, sock->ai_addr, (int)sock->ai_addrlen) != 0) // sizeof(server_addr) ***** use this for length retrieval?
		{
			cout << "Server connection failed...." << endl;
			return;
		}
	}

	// failed connection
	if (socket_d == INVALID_SOCKET)
	{
		cout << "Server connection failed..." << endl;
		return;
	}

	// Server address info no longer necessary
	freeaddrinfo(addr_result);

	// disable bloacking
	u_long iMode = 1;
	ioctlsocket(socket_d, FIONBIO, &iMode);

	// disable nagle algorithm (can cause latency issues)
	char value = 1;
	setsockopt(socket_d, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

// destructor
Client::~Client() {}