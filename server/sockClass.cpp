#include "sockClass.h"
#include "globalState.h"
mySocket::mySocket(int& port, logger& lg) : portno(port), lg(&lg) {

    buf = "Сокет: Инициализвация сокета с портом: " + std::to_string(port);
    lg.logStr(buf);

    #ifdef DEBUG
    std::cout << "### mySock::mySock\n";
    #endif // DEBUG
}
mySocket::~mySocket() {
    if (!(sockfd < 0)) close(sockfd);
    if (!(newsockfd < 0)) close(newsockfd);
    #ifdef DEBUG
    std::cout << "### mySock::~mySock Удаление двух сокетов\n";
    #endif // DEBUG
}
void mySocket::initializeSocket() {
    #ifdef DEBUG
    std::cout << "### mySocket::initializeSocket Создание сокета\n";
    #endif // DEBUG

    // if (!(newsockfd < 0)) close(newsockfd);
    // if (!(sockfd < 0)) close(sockfd);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) throw "mySocket::initializeSocket: SocketException";

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (sockaddr*) &serv_addr,
        sizeof(serv_addr)) > 0) throw "mySocket::initializeSocket: SocketException";

    #ifdef DEBUG
    std::cout << "### mySocket::initializeSocket Сокет создан и привязан\n";
    #endif // DEBUG
}
void mySocket::connectWithClient() {
    #ifdef DEBUG
    std::cout << "### mySocket::connectWithClient: Start\n";
    #endif // DEBUG

    close(newsockfd);

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0) throw "mySocket::connectWithClient: error on accept\n";

    buf = inet_ntoa(cli_addr.sin_addr);
    buf = "Сокет: Подключение с " + buf;

    lg->logStr(buf);

    #ifdef DEBUG
    std::cout << "### mySocket::connectWithClient: End\n";
    #endif // DEBUG
}
void mySocket::readFromSocket() {
    #ifdef DEBUG
    std::cout << "### mySocket::readFromSocket: Start\n";
    #endif // DEBUG

    if (newsockfd < 0) throw "mySocket::readFromSocket: error on accept\n";
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) throw "mySocket::readFromSocket: error on read\n";

    for(int i{}; i < 255; ++i) {
        if (buffer[i] == '\n') buffer[i] = ' ';
    }

    buf = inet_ntoa(cli_addr.sin_addr);
    buf = "Сокет: Чтение с " + buf;

    lg->logStr(buf);

    #ifdef DEBUG
    std::cout << "### mySocket::readFromSocket: End\n";
    #endif // DEBUG
}
void mySocket::writeToSocket(char* data, size_t len) {
    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: Start\n";
    #endif // DEBUG

    if (newsockfd < 0) throw "mySocket::writeToSocket: error on accept\n";
    n = write(newsockfd, data, len);
    if (n < 0) throw "mySocket::writeToSocket: error on write\n";

    buf = inet_ntoa(cli_addr.sin_addr);
    buf = "Сокет: Запись в " + buf;

    lg->logStr(buf);

    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: End\n";
    #endif // DEBUG
}
void mySocket::writeToSocket(const char* data, size_t len) {
    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: Start\n";
    #endif // DEBUG

    if (newsockfd < 0) throw "mySocket::writeToSocket: error on accept\n";
    n = write(newsockfd, data, len);
    if (n < 0) throw "mySocket::writeToSocket: error on write\n";

    buf = inet_ntoa(cli_addr.sin_addr);
    buf = "Сокет: Запись в " + buf;

    lg->logStr(buf);

    #ifdef DEBUG
    std::cout << "### mySocket::writeToSocket: End\n";
    #endif // DEBUG
}
char* mySocket::getBuffer() {
    return buffer;
}
// void mySocket::reConnectWithClient() {
//     #ifdef DEBUG
//     std::cout << "### mySocket::reConnectWithClient: Start\n";
//     #endif // DEBUG

//     ini

//     #ifdef DEBUG
//     std::cout << "### mySocket::reConnectWithClient: End\n";
//     #endif // DEBUG
// }