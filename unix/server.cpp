#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{
    cout << "Start!" << endl;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char readBuffer[1024];
    const char *hey = "Hey there from the server\n";

    cout << "Opening socket..." << endl;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        cerr << "Failed to open socket" << endl;
        exit(EXIT_FAILURE);
    }

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    cout << "Binding socket..." << endl;
    if (bind(sockfd, (sockaddr *)&address, sizeof(address)) < 0)
    {
        cerr << "Failed to bind socket" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Listening on socket..." << endl;
    if (listen(sockfd, 3) < 0)
    {
        cerr << "Failed to listen on socket" << endl;
        exit(EXIT_FAILURE);
    }

    int socketConnetction = accept(sockfd, (sockaddr *)&address, (socklen_t *)&addrlen);
    if (socketConnetction < 0)
    {
        cerr << "Failed to accept connection" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Accepted connection!" << endl;

    cout << "Sending message..." << endl;
    if (send(socketConnetction, hey, strlen(hey) + 1, 0) < 0)
    {
        cerr << "Send failed!" << endl;
    };

    cout << "Reading message..." << endl;
    if (read(socketConnetction, readBuffer, 24) < 0)
    {
        cerr << "Read failed!" << endl;
        exit(EXIT_FAILURE);
    };

    printf("%s", readBuffer);

    close(socketConnetction);

    return shutdown(sockfd, SHUT_RDWR);
}