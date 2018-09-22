#include "GameClientSide.h" 

// constructor
GameClientSide::GameClientSide(char* server, Ship& possess) : address(server)
{
	// client obj
	client = new Client(address, possess);

	/*// send connection packet	
	 // message obj
	message.message_type = CONNECT; //  give type
	const unsigned int message_size = sizeof(Message); //  give size
	char message_data[message_size];	// array of size
	message.serialize(message_data);	// serialise
	// send*/
	//NetworkManager::sendMessage(client->socket_d, message_data);
}

// destructor
GameClientSide::~GameClientSide() 
{
	delete client;
	delete address;
}

void GameClientSide::UpdateGame()
{
	int buffer = client->recvMessages(messageData);
	if (buffer <= 0)
		return;

	/*
	// iterater
	int i = 0;

	while (i < strlen(messageData))
	{
		message.deserialize(&(messageData[i]));
		i += sizeof(Message);

		switch (message.message_type) 
		{
			case ACTION:
				std::cout << "Received ACTION message from server" << std::endl;
				sendACTION(); break;
			default:
				std::cout << "Error in MESSAGE types" << std::endl;	break;
		}
	}
	*/
}

void GameClientSide::sendACTION()
{
	/*// send action packet
	char messageData[sizeof(Message)];

	Message message;
	message.message_type = ACTION;

	message.serialize(messageData);
	*/
	NetworkManager::sendMessage(client->socket_d, messageData);
}