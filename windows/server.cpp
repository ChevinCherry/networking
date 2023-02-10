#include <string.h>
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>
#include "../Client.h"

using namespace std;

int main()
{
    cout << "Start!" << endl;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char readBuffer[1024];
    const char *hey = "Hey there from the server\n";
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "Failed WSAStartup" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Opening socket..." << endl;
    SOCKET connectionsSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectionsSocket < 0)
    {
        cerr << "Failed to open socket" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    cout << "Binding socket..." << endl;
    if (bind(connectionsSocket, (sockaddr *)&address, sizeof(address)) < 0)
    {
        cerr << "Failed to bind socket" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    cout << "Listening on socket..." << endl;
    if (listen(connectionsSocket, 3) < 0)
    {
        cerr << "Failed to listen on socket" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    SOCKET clientSocket = accept(connectionsSocket, (sockaddr *)&address, (socklen_t *)&addrlen);
    if (clientSocket == INVALID_SOCKET)
    {
        cerr << "Failed to accept connection" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    cout << "Accepted connection!" << endl;

    cout << "Sending message..." << endl;
    if (send(clientSocket, hey, strlen(hey) + 1, 0) < 0)
    {
        cerr << "Send failed!" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    };

    cout << "Reading message..." << endl;
    if (recv(clientSocket, readBuffer, 24, 0) < 0)
    {
        cerr << "Read failed!" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    };

    printf("%s", readBuffer);

    closesocket(clientSocket);
    shutdown(connectionsSocket, SD_BOTH);
    WSACleanup();

    return 0;
}