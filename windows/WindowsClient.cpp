#include "./WindowsClient.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

WindowsClient::WindowsClient()
{
    cliSocket = INVALID_SOCKET;
};

int WindowsClient::open(const char *ipAddress, int port)
{
    if (port > 99999)
    {
        cerr << "Invalid Port: " << port << endl;
        return 1;
    }
    char portBuffer[6];
    struct addrinfo addrIn;
    memset(&addrIn, 0, sizeof(addrIn));
    struct addrinfo *addrOut;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    {
        cerr << "WSAStartup failure" << endl;
        return 1;
    }

    addrIn.ai_family = AF_INET;
    addrIn.ai_socktype = SOCK_STREAM; // TCP
    addrIn.ai_protocol = IPPROTO_TCP;

    itoa(port, portBuffer, 10);
    if (getaddrinfo(ipAddress, portBuffer, &addrIn, &addrOut) != NO_ERROR)
    {

        cerr << "Error getting address info" << endl;
        WSACleanup();
        return 1;
    }

    SOCKET openedSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (openedSocket == INVALID_SOCKET)
    {
        cerr << "Invalid socket opened" << endl;
        WSACleanup();
        return 1;
    }
    if (connect(openedSocket, addrOut->ai_addr, addrOut->ai_addrlen) != NO_ERROR)
    {
        cerr << "Failed to connect" << endl;
        freeaddrinfo(addrOut);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(addrOut);
    cliSocket = openedSocket;
    return 0;
};

int WindowsClient::sendPacket(void *packet, int packetSize)
{
    return send(cliSocket, (char *)packet, packetSize, 0);
}

int WindowsClient::receivePacket(void *dest, int recvSize)
{
    return recv(cliSocket, (char *)dest, recvSize, 0);
};

int WindowsClient::close()
{
    closesocket(cliSocket);
    WSACleanup();
    cliSocket = INVALID_SOCKET;
    return 0;
};