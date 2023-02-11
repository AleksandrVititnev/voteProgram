#ifndef SOCKCLASS_H
#define SOCKCLASS_H
#include <iostream>
// #include <cstdio>
// #include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <exception>
class mySocket {
private:
    int sockfd, portno, n;
    sockaddr_in serv_addr;
    char buffer[256];
public:
    mySocket() = default;
    mySocket(int&);
    ~mySocket();
    void initializeSocket(char*);
    void connectToServer();
    void reConnectToServer();
    void readFromSocket();
    void writeToSocket(char*, size_t);
    void writeToSocket(const char*, size_t);
    char* getBuffer();
    void closeSocket();
};
#endif // SOCKCLASS_H