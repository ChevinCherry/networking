#pragma once
#include <WinSock2.h>
#include "../Server.h"

using namespace std;

class WindowsServer : public Server
{
private:
    SOCKET connectionSocket;
    struct sockaddr_in address;
    int addrlen;
    SOCKET *connections;
    int maxConnections;

public:
    WindowsServer();
    virtual int start(int port, int numConnections);
    virtual int awaitConnection(int index);
    virtual int sendPacket(void *packet, int packetSize, int clientIndex);
    virtual int receivePacket(void *dest, int recvSize, int clientIndex);
    virtual int closeConnection(int index);
    virtual int end();
};