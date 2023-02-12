#pragma once

class Client
{
public:
    virtual int open(const char *ipAddress, int port) = 0;
    virtual int sendPacket(void *packet, int packetSize) = 0;
    virtual int receivePacket(void *dest, int recvSize) = 0;
    virtual int close() = 0;
};