#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

// send
int NetworkManager::sendMessage(SOCKET socket_d, char * messageOut) 
{
	// try send
	int result = send(socket_d, messageOut, sizeof(messageOut), 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		std::cout << "WinSock Error: " << WSAGetLastError() << std::endl;
}

// send (to all)
void NetworkManager::sendAll(char * messages)
{
	// iterater // Why isn't this workingggggg **********************
	std::map<unsigned int, SOCKET>::iterator i;

	// socket obj
	SOCKET socket_d;

	for (i = clients_map.begin(); i != clients_map.end(); i++)
	{
		socket_d = i->second;
		int result = NetworkManager::sendMessage(socket_d, messages);

		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(socket_d);
		}
	}
}

// recv
int NetworkManager::recvMessage(SOCKET socket_d, char * messageIn) 
{
	// try receive
	int result = recv(socket_d, messageIn, sizeof(messageIn), 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		std::cout << "Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
}