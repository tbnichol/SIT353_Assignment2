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