#pragma once

#pragma once
#include "Client.h"

class Server
{
public:
    virtual int start(int port, int numConnections) = 0;
    virtual int awaitConnection(int index) = 0;
    virtual int sendPacket(void *packet, int packetSize, int clientIndex) = 0;
    virtual int receivePacket(void *dest, int recvSize, int clientIndex) = 0;
    virtual int closeConnection(int index) = 0;
    virtual int end() = 0;
};