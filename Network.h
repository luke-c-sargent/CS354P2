#pragma once

#include <Ogre.h>
#include "BaseApplication.h"

enum NetworkState{GAME_SINGLE,GAME_CLIENT,GAME_SERVER};

class Network {

public:
    Network(int,BaseApplication *);
    void waitForConnection(int);
    void searchForConnection(int, std::string);
    void writeSendBuffer(char *);
    bool sendPacket(int len=0);
    bool receivePacket();
    bool closeConnections();
    BaseApplication* baseapp;
    bool connected;

    void setState(int);


    NetworkState curState;
    int clientsockfd;
    int serversockfd;

    char buffer[256];

    char toSendPacket[256];
    bool sendPacketReady;

    char toRecPacket[256];
    void printpacket(char *);

};
