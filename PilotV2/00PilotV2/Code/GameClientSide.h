/* 
#pragma once
#include "Client.h" // Allows for utilisation of Client class functions and attributes

class GameClientSide
{
public:
	GameClientSide(char* server, Ship& possess);
	~GameClientSide();

	// client obj
	Client* client;

	void sendACTION();
	void UpdateGame();

	char* address;
	char messageData[DEFAULT_BUFFER_LENGTH];
};
*/

