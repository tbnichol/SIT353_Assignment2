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

class Client
{
public:	
	Client(char* address, Ship& possess); // constructor
	~Client();	// destructor

	void Update();
	int recvMessages(char * buffer);
	
	// Connection socket 
	SOCKET socket_d = INVALID_SOCKET;	// initialise to invalid (temp)
	Ship * player_ship;
	std::thread * networkThread;

	ShipNetData shipNet;
	ShipSendData shipSend;
	// For error checking
	int result;
};