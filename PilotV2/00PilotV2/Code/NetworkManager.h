#pragma once

#include <winsock2.h>
#include <Windows.h>
#include <iostream> // Used for Debug

// ShipNetData contains data to send over the network. ShipSendData allows us to grab an array of bytes of said data.
struct ShipNetData { double posx, posy, direction; /* to discuss what we exactly need */ };
union ShipSendData { ShipNetData s_data; char* buffer[sizeof(ShipNetData)]; };

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	static void sendToClient(SOCKET socket_d, char * messageOut);
	static void recvFromClient(SOCKET socket_d, char * messageIn);

	enum ManagerType { SERVER, CLIENT };
};