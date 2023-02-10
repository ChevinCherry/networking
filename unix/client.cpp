#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

int main() {

    char hey[] = "Hey dog what's crackin\n";
    cerr << "Opening socket..." << endl;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    char buffer[1024];
    

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    cerr << "Attempting connection..." << endl;
    if (connect(sockfd, (sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Connection failure" << endl;
        exit(EXIT_FAILURE);
    }
    cerr << "Connection successful!" << endl;

    cerr << "Reading message..." << endl;
    read(sockfd, buffer, 1024);

    printf("%s", buffer);

    cerr << "Sending message..." << endl;
    int sendRes = write(sockfd, hey, strlen(hey) + 1);
    if (sendRes < 0) {
        cerr << "Failed to send message" << endl;
        exit(EXIT_FAILURE);
    }
    
    // printf("%s\n", buffer);
    close(sockfd);

    return 0;

}