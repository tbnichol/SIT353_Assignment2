#include "Client.h"

// constructor
Client::Client(char* address, Ship& ship) : player_ship(&ship)
{
	// Messy process with windows networking - "start" the networking API.
	WSADATA wsaData; // Stores win socket init info
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Stores address info (for socket connection)
	struct addrinfo *addr_result = NULL, *sock = NULL, addr_info;
	ZeroMemory(&addr_info, sizeof(addr_info));	// Sets size
	addr_info.ai_family = AF_INET;				// IPV4
	addr_info.ai_socktype = SOCK_STREAM;		// TCP
	addr_info.ai_protocol = IPPROTO_TCP;		// TCP	
									  
	//resolve server address and port
	// TO DO: potentially change this as it is currently set to localhost
	// *******************************************************************
	getaddrinfo(address, DEFAULT_PORT, &addr_info, &addr_result);
	// inet_pton(AF_INET, server_IP, &(server_addr.sin_addr.s_addr)); ***
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
			std::cout << "Server connection failed...." << std::endl;
			break;
		}
	}

	// failed connection
	if (socket_d == INVALID_SOCKET)
	{
		std::cout << "Server connection failed..." << std::endl;
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

	networkThread = new std::thread(&Client::Update, this);
}

// destructor
Client::~Client() {}

void Client::Update() {
	while (true)
	{
		ShipNetData i;
		player_ship->getPosition(i.posx, i.posy);
		ShipSendData j;
		j.s_data = i;
		NetworkManager::sendMessage(socket_d, *j.buffer);
	}
}
