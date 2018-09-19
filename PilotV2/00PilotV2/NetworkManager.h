#pragma once

#include <thread>
#include <vector>

#include "Code\Ship.h"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void sendToClients(/* Add function parameters when ready*/);
	void recvFromClients(/* Add function parameters when ready*/);


private:

	char* formatShip(Ship& x);
	Ship formatShip(char* buffer);

	union ShipData {
		Ship u_ship;
		char* buffer[sizeof(Ship)];
	};
};

