#pragma once

#include <Ogre.h>
//#include "BaseApplication.h"

enum NetworkState{GAME_SINGLE,GAME_CLIENT,GAME_SERVER};

class Network {

public:
	Network(int);
	void waitForConnection(int);
	void searchForConnection(int, std::string);
	bool sendPacket(char *);
	bool receivePacket(char *);
	bool closeConnections();

	NetworkState curState;
	int clientsockfd;
	int serversockfd;
	char buffer[256];

};

