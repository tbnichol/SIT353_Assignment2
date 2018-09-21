#pragma once

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "NetworkManager.h"
#include <ws2tcpip.h>
#include <stdio.h> 

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

class Client
{
public:	
	Client();		// constructor
	~Client();		// destructor
	
	// Connection socket 
	SOCKET socket_d = INVALID_SOCKET; // initialise to invalid (temp)

	// For error checking
	int result;
};