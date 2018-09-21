//#pragma once
#include "Server.h" // Allows for utilisation of Server class functions and attributes

class GameServerSide
{
	// server obj
	Server* server;
	static unsigned int clientID;
	
public:
	GameServerSide();
	~GameServerSide();

	void UpdateGame();

	// TO DO: include all game stuff eventually.... *****
};
