#include "GameClientSide.h" 

// constructor
GameClientSide::GameClientSide(char* server, Ship& possess) : address(server)
{
	// client obj
	client = new Client(address, possess);

	// send connection packet	
	Message message; // message obj
	message.message_type = CONNECT; //  give type
	const unsigned int message_size = sizeof(Message); //  give size
	char message_data[message_size];	// array of size
	message.serialize(message_data);	// serialise
	// send
	NetworkManager::sendMessage(client->socket_d, message_data);
}

// destructor
GameClientSide::~GameClientSide() 
{
	delete client;
	delete address;
}