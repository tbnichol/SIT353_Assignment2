#include "NetworkManager.h"
<<<<<<< HEAD
#include <iostream> // Used for Debug
=======
>>>>>>> 84eb8fecc9c060438542d04f32a00ba7920e12d4

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

<<<<<<< HEAD
void NetworkManager::sendToClient(SOCKET socket_d, char * messageOut) {
	if (send(socket_d, messageOut, sizeof(messageOut), 0) == SOCKET_ERROR) {
		std::cout << "Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
	}
}

void NetworkManager::recvFromClient(SOCKET socket_d, char * messageIn) {
	if (recv(socket_d, messageIn, sizeof(messageIn), 0) == SOCKET_ERROR) {
		std::cout << "Error!: Check WinSock Error Code " << WSAGetLastError() << std::endl;
	}
=======
// sender
void NetworkManager::sendToClient(SOCKET socket_d, char * messageOut) {
	send(socket_d, messageOut, sizeof(messageOut), 0);
}
// reciever
void NetworkManager::recvFromClient(SOCKET socket_d, char * messageIn) {
	recv(socket_d, messageIn, sizeof(messageIn), 0);
>>>>>>> 84eb8fecc9c060438542d04f32a00ba7920e12d4
}