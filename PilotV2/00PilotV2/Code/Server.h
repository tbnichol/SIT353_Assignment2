#pragma once
#include "NetworkManager.h"
#include "Client.h"

#include <ws2tcpip.h>
#include <map>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

struct Player {
	std::string p_name;
	SOCKET p_socket;
	Ship& p_ship;
};

class Server
{
public:
	// Initialise
	Server();
	~Server();

	// Sockets
	SOCKET listen_socket_d = INVALID_SOCKET;;		// listening
	SOCKET connection_socket_d = INVALID_SOCKET;; // client connection

	// For error checking
	int result;

	// table to store client sockets
	std::map<unsigned int, SOCKET> clients_map;
	std::vector<Player> client_vec;

	// Accepts client connections
	bool addClient(unsigned int & clientID);
	void checkForClientUpdates();
	void castClientChanges();
};