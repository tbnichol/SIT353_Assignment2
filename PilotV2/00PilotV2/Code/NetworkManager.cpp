#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

// send
void NetworkManager::sendToClient(SOCKET socket_d, char * messageOut) {
	send(socket_d, messageOut, (int)strlen(messageOut), 0);
}
// recv
void NetworkManager::recvFromClient(SOCKET socket_d, char * messageIn) {
	recv(socket_d, messageIn, (int)strlen(messageIn), 0);
}