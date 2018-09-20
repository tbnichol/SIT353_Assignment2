#pragma once

#include <winsock2.h>
//#include <windows.h>

#include <thread>
#include <vector>
#include <iostream> // 
#include <ws2tcpip.h> // 
#include <map> //

using namespace std; // 


class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	void sendToClient(SOCKET socket_d, char * messageOut);
	void recvFromClient(SOCKET socket_d, char * messageIn);

	// ShipNetData contains data to send over the network. ShipSendData allows us to grab an array of bytes of said data.
	inline struct ShipNetData { int posx, posy, direction; /* to discuss what we exactly need */ };
	inline union ShipSendData { ShipNetData s_data; char* buffer[sizeof(ShipNetData)]; };

	enum ManagerType { SERVER, CLIENT };
};