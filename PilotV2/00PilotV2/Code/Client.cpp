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

	network_thread = new std::thread(&Client::update, this);
}

// destructor
Client::~Client() {
	// delete some things.... **********
}

// update client
void Client::update() {
	while (true)
	{
		// update position
		player_ship->getPosition(ship_net.posx, ship_net.posy);

		// message type ( a == action)
		ship_net.msgType = 'a';

		// set send data to action 
		ship_send.s_data = ship_net;

		// send update
		NetworkManager::sendMessage(socket_d, ship_send.buffer);
		
		// recieve updates
		if (recvMessages(ship_send.buffer) > 0)
			player_ship->setPosition(ship_send.s_data.posx, ship_send.s_data.posy);

	}
}

int Client::recvMessages(char * buffer)
{
	result = NetworkManager::recvMessage(socket_d, buffer);

	// successful
	if (result != 0)
		return result;
	// unseccessful
	else
	{
		std::cout << "Connection closed" << std::endl;
		closesocket(socket_d);
		WSACleanup();
		return -1;
	}	
}
