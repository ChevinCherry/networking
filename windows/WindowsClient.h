#pragma once
#include <WinSock2.h>
#include "../Client.h"

class WindowsClient : public Client
{
private:
    SOCKET cliSocket;

public:
    WindowsClient();
    virtual int open(const char *ipAddress, int port);
    virtual int sendPacket(void *packet, int packetSize);
    virtual int receivePacket(void *dest, int recvSize);
    virtual int close();
};