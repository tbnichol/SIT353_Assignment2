#pragma once

#include <winsock2.h>
#include <Windows.h>
#include "NetworkManager.h"
#include <ws2tcpip.h>
#include <stdio.h> 

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// defines
#define DEFAULT_BUFLEN 512		// Buffer
#define DEFAULT_PORT "33303"	// Port 
//	TO DO: Change the port to be dependant

class Client
{
public:	
	// For error checking
	int iResult;	

	// Connection socket 
	SOCKET ConnectSocket;	

	Client(void);		// constructor
	~Client(void);		// destructor
};