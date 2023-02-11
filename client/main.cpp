#include "header.h"
#include "sockClass.h"
#include "dataClass.h"
#include "findFile.h"
#include "additionalFunctions.h"
#include "globalState.h"

//./App -p 1234 -i 127.0.0.1
int main(int argc, char** argv) {
//Variables
    std::string buffer;
    int temp = 0, amountLayers = 0;
    mySocket* socket = nullptr;
    dataClass* myList = nullptr;
    char* ip = nullptr;
    char** data = nullptr;
//Variables end

    if (argc <= 4 || argc > 5) {
        std::cout << "Invalid arguments\n";
        exit(1);
    }

//Configuration
    for (int i{1}; i < argc; i+=2) {
        buffer = argv[i];
        if (buffer == "-p" || buffer == "--port") {
            #ifdef DEBUG
            std::cout << "### Configuration port\n";
            #endif //DEBUG
            temp = atoi(argv[i + 1]);
            if (temp <= 0) {
                std::cout << "Invalid port\n";
                exit(1);
            }
            else {
                socket = new mySocket(temp);
            }
        }
        else if (buffer == "-i" || buffer == "--ip") {
            #ifdef DEBUG
            std::cout << "### Configuration ip\n";
            #endif //DEBUG
            ip = argv[i + 1];
        }
        else {
            if (!ip) {
                std::cout << "You must provide an IP address\n";
                if (!socket) delete socket;
                exit(1);
            }
        }
    }
//Configuration end

//Initialize socket
    try {
        socket->initializeSocket(ip);
    }
    catch (const char* ex) {
        std::cout << "!!! Error: " << ex << std::endl;
        perror("This");
        delete socket;
    }
//Initialize socket end

//Basic code
    try {
        socket->connectToServer();
        socket->writeToSocket("g", 2);
        socket->readFromSocket();

        if (socket->getBuffer()[0] == '^') amountLayers = 4;
        else amountLayers = 1;

        data = new char*[amountLayers];
        data[0] = new char[256];
        copyChar(socket->getBuffer(), data[0], 256);
        #ifdef DEBUG
        std::cout << "#####" << socket->getBuffer() << std::endl;
        #endif //DEBUG
        for (int i{1}; i < amountLayers; i++) {
            socket->readFromSocket();
            data[i] = new char[256];
            copyChar(socket->getBuffer(), data[i], 256);
            #ifdef DEBUG
            std::cout << "#####" << socket->getBuffer() << '\n';
            #endif //DEBUG
            //if (socket->getBuffer()[0] != '^') amountLayers = i + 1;
        }
        myList = new dataClass(getAmountCand(data, amountLayers));
        
        fillList(data, amountLayers, myList);
        for (int i{}; i < myList->getAmount(); ++i) {
            std::cout << i + 1 << ": " << myList->getName(i) << '\n';
        }
        std::cout << "Select candidate:";
        std::cin >> temp;
        if (temp <= 0 || temp > myList->getAmount()) throw std::invalid_argument("Error select must be greater than 0 or less than Amount");

        temp--;

        socket->closeSocket();
        socket->initializeSocket(ip);
        socket->connectToServer();
        socket->writeToSocket("s", 2);
        system("sleep 1");
        socket->writeToSocket(myList->getId(temp).c_str(), myList->getId(temp).length());
        while(true) {
            socket->readFromSocket();
            //buffer = socket->getBuffer();
            if (socket->getBuffer()[0] == 'e') {
                socket->writeToSocket(myList->getId(temp).c_str(), myList->getId(temp).length());
            }
            else {
                break;
            }
        }

    }
    catch(const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    catch (const char* ex) {
        std::cout << "Error: " << ex << std::endl;
    }
    for (int i{}; i < amountLayers; ++i) delete[] data[i];
    delete[] data;
    delete myList;
    delete socket;
    return 0;
}