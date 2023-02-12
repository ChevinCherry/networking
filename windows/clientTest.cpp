#include "WindowsClient.h"
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    WindowsClient client = WindowsClient();
    client.open("127.0.0.1", 8080);
    char buffer[1024];
    const char *sendStr = "Test client packet";
    client.sendPacket((void *)sendStr, strlen(sendStr) + 1);
    client.receivePacket(buffer, 1024);
    printf("%s", buffer);
    client.close();
}