#include "GameClientSide.h" 

// constructor
GameClientSide::GameClientSide(char* server, Ship& possess) : address(server)
{
	// client obj
	client = new Client(address, possess);
}

// destructor
GameClientSide::~GameClientSide() 
{
	delete client;
	delete address;
}