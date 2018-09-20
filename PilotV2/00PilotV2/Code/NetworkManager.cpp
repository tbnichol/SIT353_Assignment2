#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

// sender
void NetworkManager::sendToClient(SOCKET socket_d, char * messageOut) {
	send(socket_d, messageOut, sizeof(messageOut), 0);
}
// reciever
void NetworkManager::recvFromClient(SOCKET socket_d, char * messageIn) {
	recv(socket_d, messageIn, sizeof(messageIn), 0);
}