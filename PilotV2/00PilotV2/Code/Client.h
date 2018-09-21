#pragma once

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "NetworkManager.h"
#include "Ship.h"

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

class Client
{
public:	
	Client(char* address, Ship& possess);		// constructor
	~Client();		// destructor

	void Update();
	
	// Connection socket 
	SOCKET socket_d = INVALID_SOCKET; // initialise to invalid (temp)
	Ship * player_ship;
	std::thread * networkThread;

	// For error checking
	int result;
};