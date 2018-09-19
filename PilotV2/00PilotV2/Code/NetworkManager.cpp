//#include "stdafx.h" // Probably not necessary
#include "NetworkManager.h"

// send
int NetworkUtility::sendData(SOCKET c_Socket, char * message, int messageSize)
{
	return send(c_Socket, message, messageSize, 0);
}
// receive
int NetworkUtility::recvData(SOCKET c_Socket, char * buffer, int bufferSize)
{
	return recv(c_Socket, buffer, bufferSize, 0);
}

NetworkManager::NetworkManager() {

}

// Used for Enum ManagerType
NetworkManager::NetworkManager(int man_type) {

}

NetworkManager::~NetworkManager() {

}

void NetworkManager::sendToClient(/* To determine parameters later */) {
	
}

void NetworkManager::recvFromClient(/* To determine parameters later */) {

>>>>>>> 802a26bcf7c69156cb8730e49d60e60de00d3976
}