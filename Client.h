class Client
{
    Client() {}
    virtual ~Client() {}
    virtual int open(const char *ipAddress, int port) = 0;
    virtual int sendPacket(void *message, int messageSize) = 0;
    virtual int recievePacket() = 0;
    virtual int close() = 0;
};