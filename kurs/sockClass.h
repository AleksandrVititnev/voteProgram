#ifndef SOCKCLASS_H
#define SOCKCLASS_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <exception>
class mySocket {
private:
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    sockaddr_in serv_addr, cli_addr;
    char buffer[256];
public:
    mySocket() = default;
    mySocket(int&);
    ~mySocket();
    void initializeSocket();
    void connectWithClient();
    void readFromSocket();
    void writeToSocket(char*, size_t);
    void writeToSocket(const char*, size_t);
    char* getBuffer();
};
#endif // SOCKCLASS_H