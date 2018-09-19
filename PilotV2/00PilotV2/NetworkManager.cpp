#include "NetworkManager.h"



NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::sendToClients(/* Add function parameters when ready*/) {
	// Gets all nessisary data for sending (ship locations, bullets) and sends to clients in a list
}

void NetworkManager::recvFromClients(/* Add function parameters when ready*/) {
	// Checks all sockets for messages and sets their values to correct ships/bullets
}

char* NetworkManager::formatShip(Ship& x) {
	ShipData s_Data;
	s_Data.u_ship = &x;
	
	return *(s_Data.buffer);
	// Use ShipData union to extract bytes
}

/*Ship NetworkManager::formatShip(char* buffer) {
	// Use ShipData union to extract bytes
	return c;
}*/