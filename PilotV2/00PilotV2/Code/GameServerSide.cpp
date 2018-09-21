#include "GameServerSide.h"

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
		std::cout << "New client connected. ID: " << clientID << std::endl;
		clientID++; //  iterate
	}
	// check for client messages
	recv_FromClient();

	// TO DO: Add in gane environment updates **************
}

void GameServerSide::recv_FromClient()
{
	// message obj
	Message message;

	// iterate through clients map
	std::map<unsigned int, SOCKET>::iterator i;
	for (i = server->clients_map.begin(); i != server->clients_map.end(); i++)
	{
		// retrieve message
		int messageLength = server->recvMessage(i->first, buffer);

		// no message retrieved
		if (messageLength <= 0)
			continue;
		else
		{
			// iterator
			int j = 0;

			while (j < (unsigned int)messageLength)
			{
				message.deserialize(&(buffer[j]));
				j += sizeof(Message);

				// add more in here eventually... ***************
				switch (message.message_type)
				{
				case CONNECT:
					std::cout << "Server received CONNECT message from client" << std::endl; break;

				case ACTION:
					std::cout << "Server received ACTION message from client" << std::endl; break;

				default:
					std::cout << "Error in MESSAGE types" << std::endl; break;
				}
			}
		}
	}
}
