#include "Client.h" // Allows for utilisation of Client class functions and attributes
//#include <Windows.h>
//#include <winsock2.h>

class GameClientSide
{
public:
	GameClientSide();
	~GameClientSide();

	// client obj
	Client* client;
};