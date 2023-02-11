#include "sockClass.h"
#include "globalState.h"
mySocket::mySocket(int& port) : portno(port) {

    #ifdef DEBUG
    std::cout << "### mySock::mySock\n";
    #endif // DEBUG
}
mySocket::~mySocket() {
    if (!(sockfd < 0)) close(sockfd);
    #ifdef DEBUG
    std::cout << "### mySock::~mySock Удаление двух сокетов\n";
    #endif // DEBUG
}
void mySocket::initializeSocket(char* ip) {
    #ifdef DEBUG
    std::cout << "### mySocket::initializeSocket Создание сокета\n";
    #endif // DEBUG

    //if (!(newsockfd < 0)) close(newsockfd);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) throw "mySocket::initializeSocket: SocketException";

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(portno);

    #ifdef DEBUG
    std::cout << "### mySocket::initializeSocket Сокет создан и привязан\n";
    #endif // DEBUG
}
void mySocket::connectToServer() {
    #ifdef DEBUG
    std::cout << "### mySocket::connectWithClient: Start\n";
    #endif // DEBUG

    n = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    if (n < 0) throw "mySocket::connectWithClient: error connecting\n";

    #ifdef DEBUG
    std::cout << "### mySocket::connectWithClient: End\n";
    #endif // DEBUG
}
void mySocket::reConnectToServer() {
    #ifdef DEBUG
    std::cout << "### mySocket::reConnectToServer: Start\n";
    #endif // DEBUG

    if (sockfd < 0) throw "mySocket::readFromSocket: error on accept\n";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connectToServer();

    #ifdef DEBUG
    std::cout << "### mySocket::reConnectToServer: End\n";
    #endif // DEBUG
}
void mySocket::readFromSocket() {
    #ifdef DEBUG
    std::cout << "### mySocket::readFromSocket: Start\n";
    #endif // DEBUG

    if (sockfd < 0) throw "mySocket::readFromSocket: error on accept\n";
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) throw "mySocket::readFromSocket: error on read\n";

    for(int i{}; i < 255; ++i) {
        if (buffer[i] == '\n') buffer[i] = ' ';
    }

    #ifdef DEBUG
    std::cout << "### mySocket::readFromSocket: End\n";
    #endif // DEBUG
}
void mySocket::writeToSocket(char* data, size_t len) {
    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: Start\n";
    #endif // DEBUG

    if (sockfd < 0) throw "mySocket::writeToSocket: error on accept\n";
    n = write(sockfd, data, len);
    if (n < 0) throw "mySocket::writeToSocket: error on write\n";

    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: End\n";
    #endif // DEBUG
}
void mySocket::writeToSocket(const char* data, size_t len) {
    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: Start\n";
    #endif // DEBUG

    if (sockfd < 0) throw "mySocket::writeToSocket: error on accept\n";
    n = write(sockfd, data, len);
    if (n < 0) throw "mySocket::writeToSocket: error on write\n";

    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: End\n";
    #endif // DEBUG
}
char* mySocket::getBuffer() {
    return buffer;
}
void mySocket::closeSocket() {
    close(sockfd);
}