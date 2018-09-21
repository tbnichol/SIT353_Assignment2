#pragma once
#include "Server.h" // Allows for utilisation of Server class functions and attributes

#include <iostream>

class GameServerSide
{
	// server obj
	Server* server;
	static unsigned int clientID;

	// buffer
	char buffer[DEFAULT_BUFFER_LENGTH];

public:
	GameServerSide();
	~GameServerSide();

	void UpdateGame();

	void recv_FromClient();
	void sendACTION();

	// TO DO: include all game stuff eventually.... *****
};
