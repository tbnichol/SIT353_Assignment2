#include "Server.h"

Server::Server(std::vector<Actor *> shipList, Controller& cont) : ship_list(&shipList), cont_ptr(&cont)
{
	// Messy process with windows networking - "start" the networking API.
	WSADATA wsaData; // Stores win socket init info
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// Stores address info (for socket listening /connection)
	struct addrinfo *addr_result = NULL, addr_info;	
	ZeroMemory(&addr_info, sizeof(addr_info));	// Sets size
	addr_info.ai_family = AF_INET;				// IPV4
	addr_info.ai_socktype = SOCK_STREAM;		// TCP 
	addr_info.ai_protocol = IPPROTO_TCP;		// TCP 
	addr_info.ai_flags = AI_PASSIVE;

	// address set to local machine
	getaddrinfo(NULL, DEFAULT_PORT, &addr_info, &addr_result);

	// Create a SOCKET for connecting to server
	listen_socket_d = socket(addr_result->ai_family, addr_result->ai_socktype, addr_result->ai_protocol);

	// disable bloacking
	u_long iMode = 1;
	ioctlsocket(listen_socket_d, FIONBIO, &iMode);

	// bind
	bind(listen_socket_d, addr_result->ai_addr, (int)addr_result->ai_addrlen);
	// listen
	result = listen(listen_socket_d, SOMAXCONN);

	// Server address info no longer necessary
	freeaddrinfo(addr_result);
}

// destructor
Server::~Server() {}

// Accepts client connections
bool Server::addClient(unsigned int & clientID)
{
	connection_socket_d = accept(listen_socket_d, NULL, NULL); // accept

	// Failed connection
	if (connection_socket_d == 0 || connection_socket_d == INVALID_SOCKET)
	{
		return false;
	}
	// Successful connection
	else
	{
		// disable nagle algorithm (can cause latency issues)
		char value = 1;
		setsockopt(connection_socket_d, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

		// Add new connection to table of client sockets - TO DEPRICATE
		Ship* temp_ship = new Ship(*cont_ptr, Ship::NETPLAYER, "New Player");
		client_vec.emplace_back(new Player(std::string("Test Player"), connection_socket_d, *temp_ship
		));


		//ship_list->push_back(temp_ship);
		// Push ship back into the list. To fix ******************************
		
		
		return true;
	}
}

void Server::recieveClientUpdates()
{

}

void Server::sendClientUpdates()
{
	ShipNetData x;
	x.msgType = 'a';
	x.posx = 5.0;
	x.posy = 5.0;
	x.direction = 4.5;

	char buffer[sizeof(x)];
	memcpy(&buffer, &x, sizeof(x));

	//send_data->s_data = *send_net;
	// Above line throws a memory exception
	for (Player* i : client_vec)
	{
		NetworkManager::sendMessage(i->p_socket, buffer);
	}
}

void Server::update()
{
	
	// Notification of new client connection being established
	if (addClient(client_id))
	{
		std::cout << "New client connected. ID: " << client_id << std::endl;
		client_id++; //  iterate
	}

	recieveClientUpdates();
	// check for client messages
	
	sendClientUpdates();
	// send any client changes
}