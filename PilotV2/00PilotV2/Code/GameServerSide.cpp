#include "GameServerSide.h"
//#include <iostream>

//using namespace std;

unsigned int GameServerSide::clientID;

// Constructor
GameServerSide::GameServerSide()
{
	// server obj
	server = new Server();
	//default ID
	clientID = 0;	
}

// Destructor
GameServerSide::~GameServerSide()
{
	delete server;
}

void GameServerSide::UpdateGame()
{
	// Notification of new client connection being established
	if (server->addClient(clientID))
	{
		cout << "A new client (" << clientID << ") has established a connection! " << endl;
		clientID++; // iterate
	}

	// TO DO: Add in gane environment updates **************
}