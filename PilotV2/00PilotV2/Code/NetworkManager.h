#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include "Ship.h"

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 

struct Player {
	Player(std::string name, SOCKET socket, Ship& ship) : p_name(name), p_socket(socket), p_ship(&ship) {};
	Player(std::string name, SOCKET socket) : p_name(name), p_socket(socket) {};
	~Player() {};
	std::string p_name;
	SOCKET p_socket;
	Ship* p_ship;
};

/* ShipNetData contains data to send over the network. 
Memcpy allows us to serialise this data into an array of chars (bytes)*/
struct ShipNetData { 
	char msgType;			// Type of message to the server
	double posx = 0;		// X Position 
	double posy = 0;		// Y Position
	double direction = 0;	// Direction of ship
	int mode = 0;			// Current State (RECOVERY or INPLAY)
};
union ShipSendData { 
	ShipNetData s_data; 
	char buffer[1000]; 
	ShipSendData() {}; 
	~ShipSendData() {}; 
};

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	static int sendMessage(SOCKET socket_d, char * messageOut);
	
	static int recvMessage(SOCKET socket_d, char * messageIn, int bufLen);

	enum ManagerType { SERVER, CLIENT };
};