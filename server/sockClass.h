#ifndef SOCKCLASS_H
#define SOCKCLASS_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <exception>
#include "logClass.h"
class mySocket {
private:
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    sockaddr_in serv_addr, cli_addr;
    logger* lg = nullptr;
    char buffer[256];
    std::string buf;
public:
    mySocket() = default;
    mySocket(int&, logger&);
    ~mySocket();
    void initializeSocket();
    void connectWithClient();
    void readFromSocket();
    void writeToSocket(char*, size_t);
    void writeToSocket(const char*, size_t);
    char* getBuffer();
};
#endif // SOCKCLASS_H