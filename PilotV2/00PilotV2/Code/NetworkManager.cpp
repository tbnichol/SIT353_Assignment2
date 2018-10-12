#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

// send
int NetworkManager::sendMessage(SOCKET socket_d, char* messageOut) 
{
	int x = strlen(messageOut);
	// try send
	int result = send(socket_d, messageOut, 20, 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		std::cout << "sendMessage WinSock Error: " << WSAGetLastError() << std::endl;
	return -1;
}


// recv
int NetworkManager::recvMessage(SOCKET socket_d, char * messageIn) 
{
	char recBuffer[DEFAULT_BUFFER_LENGTH];
	// try receive
	int result = recv(socket_d, recBuffer, DEFAULT_BUFFER_LENGTH, 0);
	
	// succesful
	if (result != SOCKET_ERROR && result != 0) {

		return result;
	}
	// unsuccessful
	else {
		std::cout << "Connection closed" << std::endl;
		closesocket(socket_d);
		WSACleanup();
		return -1;
		std::cout << "recvMessage Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;

	}
}