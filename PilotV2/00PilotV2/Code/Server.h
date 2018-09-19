#pragma once

#include <winsock2.h>
#include <Windows.h>
#include "NetworkManager.h"
#include <ws2tcpip.h>
#include <map>

#pragma comment (lib, "Ws2_32.lib")

// defines
#define DEFAULT_BUFLEN 512		// Buffer
#define DEFAULT_PORT "33303"	// Port 
//	TO DO: Change the port to be dependant

using namespace std;

class Server
{
public:
	Server(void);
	~Server(void);

	// listening socket
	SOCKET listen_Socket;

	// Socket to give clients
	SOCKET client_Socket;

	// For error checking
	int iResult;

	// table to store client sockets
	std::map<unsigned int, SOCKET> sessions;
};