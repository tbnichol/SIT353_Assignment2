#include "Client.h"

// Constructor //
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
									  
	getaddrinfo(address, DEFAULT_PORT, &addr_info, &addr_result);

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
}

// Destructor // 
Client::~Client() {
	// disconnect client
	std::cout << "Client " << this->socket_d << "disconnected. Connection closed..." << std::endl;
	closesocket(this->socket_d);

	delete player_ship;
}

// Update Client //
void Client::update() {
	while (true)
	{
		// update position

		// ** EXAMPLE DATA ** //
		// message type
		ship_net.msgType = 'b';
		ship_net.direction = 5.0;
		ship_net.posx = 4.72094690284;
		ship_net.posy = 20.72094690284;

		ship_net.direction = player_ship->direction;
		ship_net.mode = player_ship->mode;
		player_ship->getPosition(ship_net.posx, ship_net.posy);
		// set send data to action 
		ship_send.s_data = ship_net;

		sendLocalUpdates();
	}
}

void Client::sendLocalUpdates()
{
	char buffer[sizeof(ship_net)];
	memcpy(&buffer, &ship_net, sizeof(ship_net));
	// send update
	NetworkManager::sendMessage(socket_d, buffer);

}
