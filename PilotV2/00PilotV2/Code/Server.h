#pragma once
#include "NetworkManager.h"
#include "Client.h"
#include "Actor.h"

#include <ws2tcpip.h>
#include <map>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

class Server 
{
public:
	// Initialise
	Server(std::vector<Actor *> ship_list);
	~Server();

	// Sockets
	SOCKET listen_socket_d = INVALID_SOCKET; // listening
	SOCKET connection_socket_d = INVALID_SOCKET; // client connection

	// For error checking
	int result; // Init Winsock
	unsigned int client_id = 0; // Unique ID

	// table to store client sockets
	std::vector<Player*> client_vec; // Stores Connected Players
	std::vector<Actor *> * ship_list; // Stores current ships
	
	// Accepts client connections	
	bool addClient(unsigned int & clientID); 
	// Detect game updates
	void recieveClientUpdates();	
	// Execute game updates
	void UpdateGame();
	// Anycast updates
	void sendClientUpdates(); 
};