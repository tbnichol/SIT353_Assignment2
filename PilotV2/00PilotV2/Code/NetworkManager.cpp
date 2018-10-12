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
	// try send
	int result = send(socket_d, messageOut, sizeof(ShipNetData), 0);
	
	// succesful
	if (result != SOCKET_ERROR) 
		return result;
	// unsuccessful
	else
		//std::cout << "sendMessage WinSock Error: " << WSAGetLastError() << std::endl;
	return -1;
}


// recv
int NetworkManager::recvMessage(SOCKET socket_d, char * messageIn, int bufLen) 
{
	// try receive
	int result = recv(socket_d, messageIn, bufLen, 0);
	
	// unsuccessful
	if (result == SOCKET_ERROR) {
		//std::cout << "recvMessage Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
		return -1;
	}
	// unsuccessful
	else if (result == 0) {
		std::cout << "Connection closed" << std::endl;
		closesocket(socket_d);
		WSACleanup();
		return -1;
	}
	// succesful
	else {
		return result;
	}
}