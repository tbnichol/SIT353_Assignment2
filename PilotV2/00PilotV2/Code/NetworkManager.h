#pragma once

#include <winsock2.h>
#include <Windows.h>

// Network functionality class
class NetworkUtility
{
public:
	static int sendData(SOCKET c_Socket, char * message, int messageSize);
	static int recvData(SOCKET c_Socket, char * buffer, int bufferSize);
};
#include <thread>
#include <vector>

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	void sendToClient(/* To determine parameters later */);
	void recvFromClient(/* To determine parameters later */);

	// ShipNetData contain data to send over the network. ShipSendData allows us to grab an array of bytes of said data.
	inline struct ShipNetData { int posx, posy, direction; /* to discuss what we exactly need */ };
	inline union ShipSendData { ShipNetData s_data; char* buffer[sizeof(ShipNetData)]; };

	enum ManagerType { SERVER, CLIENT };

>>>>>>> 802a26bcf7c69156cb8730e49d60e60de00d3976
};