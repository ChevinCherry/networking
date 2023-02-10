#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main()
{
    WSADATA wsaData;
    char hey[] = "Hey dog what's crackin\n";
    char buffer[1024];

    struct addrinfo hints;
    struct addrinfo *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "Failed WSAStartup" << endl;
        exit(EXIT_FAILURE);
    }

    if (getaddrinfo("127.0.0.1", "8080", &hints, &result) != 0)
    {
        cerr << "Failed to get address" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    };

    SOCKET connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectionSocket == INVALID_SOCKET)
    {
        cerr << "Failed to create socket" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    cerr << "Attempting connection..." << endl;
    int connectResult = connect(connectionSocket, result->ai_addr, result->ai_addrlen) != 0;
    if (connectResult != 0)
    {
        cerr << "Connection failure - Error code: " << connectResult << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    cerr << "Reading message..." << endl;
    if (recv(connectionSocket, buffer, 1024, 0) < 0)
    {
        cerr << "Failed to receive data" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("%s", buffer);

    cerr << "Sending message..." << endl;
    int sendRes = send(connectionSocket, hey, strlen(hey) + 1, 0);
    if (sendRes < 0)
    {
        cerr << "Failed to send message" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    closesocket(connectionSocket);
    WSACleanup();

    return 0;
}