//#include <winsock2.h>
//#include <Windows.h>
#include "Client.h" // Allows for utilisation of Client class functions and attributes


class GameClientSide
{
public:
	GameClientSide();
	~GameClientSide();

	// client obj
	Client* client;
};