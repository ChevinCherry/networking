#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "WindowsServer.h"

using namespace std;

WindowsServer::WindowsServer()
{
    maxConnections = 0;
    connectionSocket = INVALID_SOCKET;
    struct sockaddr_in tempAddr;
    address = *new struct sockaddr_in;
    addrlen = sizeof(address);
    connections = nullptr;
};

int WindowsServer::start(int port, int numConnections)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "Failed WSAStartup" << endl;
        return 1;
    }

    SOCKET newSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (newSocket == INVALID_SOCKET)
    {
        cerr << "Failed to open socket" << endl;
        WSACleanup();
        return 1;
    }

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (bind(newSocket, (sockaddr *)&address, sizeof(address)) < 0)
    {
        cerr << "Failed to bind socket" << endl;
        WSACleanup();
        return 1;
    }

    if (listen(newSocket, 3) < 0)
    {
        cerr << "Failed to listen on socket" << endl;
        WSACleanup();
        return 1;
    }
    connectionSocket = newSocket;
    connections = new SOCKET[numConnections];
    for (int i = 0; i < numConnections; i++)
    {
        connections[i] = INVALID_SOCKET;
    }
    maxConnections = numConnections;
    cerr << "Successfully opened" << endl;
    return 0;
};

int WindowsServer::awaitConnection(int index)
{
    if (index < 0 && index > maxConnections)
    {
        cerr << "Invalid index" << endl;
        return 1;
    }
    SOCKET clientSocket = accept(connectionSocket, (sockaddr *)&address, (socklen_t *)&addrlen);
    if (clientSocket == INVALID_SOCKET)
    {
        cerr << "Failed to accept connection" << endl;
        return 1;
    }
    connections[index] = clientSocket;
    return 0;
}

int WindowsServer::closeConnection(int index)
{
    closesocket(connections[index]);
    connections[index] = INVALID_SOCKET;
    return 0;
}

int WindowsServer::sendPacket(void *packet, int packetSize, int clientIndex)
{
    if (clientIndex < 0 || clientIndex >= maxConnections)
    {
        cerr << "Invalid client index" << endl;
        return 1;
    }
    return send(connections[clientIndex], (char *)packet, packetSize, 0);
}

int WindowsServer::receivePacket(void *dest, int recvSize, int clientIndex)
{
    if (clientIndex < 0 || clientIndex >= maxConnections)
    {
        cerr << "Invalid client index" << endl;
        return 1;
    }
    return recv(connections[clientIndex], (char *)dest, recvSize, 0);
}

int WindowsServer::end()
{
    for (int i = 0; i < maxConnections; i++)
    {
        if (connections[i] != INVALID_SOCKET)
        {
            closesocket(connections[i]);
        }
    }
    delete[] connections;
    shutdown(connectionSocket, SD_BOTH);
    connectionSocket = INVALID_SOCKET;
    maxConnections = 0;
    WSACleanup();
    return 0;
}
