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
	Client(char* address, Ship& ship); // constructor
	~Client();	// destructor
	
	// Connection socket 
	SOCKET socket_d = INVALID_SOCKET;	// initialise to invalid (temp)
	
	// player
	Ship * player_ship;

	// client thread
	std::thread * network_thread;

	// Shop (player) data
	ShipNetData ship_net;
	ShipSendData ship_send;

	// client obj
	// Client* client;

	void update();
	int recvMessages(char * buffer);

	//char* address;
	//char messageData[DEFAULT_BUFFER_LENGTH];
	//void sendACTION();
	//void UpdateGame();

	// For error checking
	int result;
};