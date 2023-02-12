#include "WindowsServer.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Starting test" << endl;
    WindowsServer server = WindowsServer();
    char buffer[1024];
    const char *sendStr = "Test server packet\n";
    server.start(8080, 1);
    server.awaitConnection(0);
    server.receivePacket(buffer, 1024, 0);
    printf("%s", buffer);
    server.sendPacket((void *)sendStr, strlen(sendStr) + 1, 0);
    server.end();
};