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

struct Player {
	Player(std::string name, SOCKET socket, Ship& ship) : p_name(name), p_socket(socket), p_ship(&ship) {};
	~Player() {};
	std::string p_name;
	SOCKET p_socket;
	Ship* p_ship;
};

class Server
{
public:
	// Initialise
	Server(std::vector<Actor *> ship_list);
	~Server();

	// Sockets
	SOCKET listen_socket_d = INVALID_SOCKET;;		// listening
	SOCKET connection_socket_d = INVALID_SOCKET;; // client connection

	// For error checking
	int result;
	unsigned int clientID;

	// table to store client sockets
	std::map<unsigned int, SOCKET> clients_map;
	std::vector<Player*> client_vec;

	std::vector<Actor *> * shipList;

	// Accepts client connections
	bool addClient(unsigned int & clientID);
	void checkForClientUpdates();
	void sendAll(char * messages); // send message to all clients 
	void UpdateGame();// (except sender);


	// receive
	int recvMessage(unsigned int clientID, char * buffer);	
};