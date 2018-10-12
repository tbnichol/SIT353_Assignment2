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

	// ship (player) data
	ShipNetData ship_net;
	ShipSendData ship_send;

	// game update
	void update();

	void sendLocalUpdates();

	// For error checking
	int result;
};