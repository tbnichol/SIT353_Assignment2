#include "NetworkManager.h"
#include <ws2tcpip.h>
#include <map>

#pragma comment (lib, "Ws2_32.lib")

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

// using namespace std; // 

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


	// Accepts client connections
	bool addClient(unsigned int & clientID);
};