#include <thread>
#include <vector>

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();

	NetworkManager(int a);

	void sendToClient(/* To determine parameters later */);
	void recvFromClient(/* To determine parameters later */);

	// ShipNetData contain data to send over the network. ShipSendData allows us to grab an array of bytes of said data.
	inline struct ShipNetData { int posx, posy, direction; /* to discuss what we exactly need */ };
	inline union ShipSendData { ShipNetData s_data; char* buffer[sizeof(ShipNetData)]; };

	enum ManagerType { SERVER, CLIENT };

};