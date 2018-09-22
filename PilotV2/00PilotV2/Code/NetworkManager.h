#pragma once

#include <winsock2.h>
#include <Windows.h>
#include <iostream> // Used for Debug
#include <map>

// defines
#define DEFAULT_BUFFER_LENGTH 512		// Buffer
#define DEFAULT_PORT "33303"			// Port 
//	TO DO: Change the port to be dependant ********

// ShipNetData contains data to send over the network. ShipSendData allows us to grab an array of bytes of said data.
struct ShipNetData { char msgType; std::string playerName; double posx, posy, direction; /* to discuss what we exactly need */ };
union ShipSendData { ShipNetData s_data; char buffer[sizeof(ShipNetData)]; ShipSendData() {}; ~ShipSendData() {}; };

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	static int sendMessage(SOCKET socket_d, char * messageOut);
	
	static int recvMessage(SOCKET socket_d, char * messageIn);

	enum ManagerType { SERVER, CLIENT };
};


// NetworkData.... **
//#define MESSAGE_MAXSIZE 1000000
// Types of message packets that can be sent
/*
enum MessageType { CONNECT = 0,	ACTION = 1,};

// to contain message data
struct Message 
{
	// type
	unsigned int message_type;

	void serialize(char * data)
	{
		memcpy(data, this, sizeof(Message));
	}

	void deserialize(char * data) 
	{
		memcpy(this, data, sizeof(Message));
	}
};*/