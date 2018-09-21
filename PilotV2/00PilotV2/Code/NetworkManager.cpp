#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

void NetworkManager::sendToClient(SOCKET socket_d, char * messageOut) {
	if (send(socket_d, messageOut, sizeof(messageOut), 0) == SOCKET_ERROR) {
		std::cout << "Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
	}
}

void NetworkManager::recvFromClient(SOCKET socket_d, char * messageIn) {
	if (recv(socket_d, messageIn, sizeof(messageIn), 0) == SOCKET_ERROR) {
		std::cout << "Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
	}
}