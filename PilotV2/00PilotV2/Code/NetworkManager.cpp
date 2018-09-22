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
	int result = send(socket_d, messageOut, (int)strlen(messageOut), 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		std::cout << "sendMessage WinSock Error: " << WSAGetLastError() << std::endl;
}


// recv
int NetworkManager::recvMessage(SOCKET socket_d, char * messageIn) 
{
	// try receive
	int result = recv(socket_d, messageIn, 512, 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		std::cout << "recvMessage Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
}