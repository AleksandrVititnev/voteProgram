#include "header.h"
#include "sockClass.h"
#include "myClass.h"
#include "findFile.h"
#include "additionalFunctions.h"
#include "globalState.h"

//./App -p or --port 25566 -c or --config file.txt
int main(int argc, char** argv) {
//Variables
    int temp = 0, amountClients = 0, layersData = 0;
    int arrayOper[2] = {0, 0};
    std::string buffer, configFileName;
    std::string startAmountCand("amountCand="), startAmountClients("amountClients=");
    char buf;
    voteList* myList;
    mySocket* socket;
    std::ifstream configFile;
    configFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//Variables end

//Check amount of arguments
    if (argc < 4 || argc > 5) {
        std::cout << "Invalid arguments\n";
        exit(1);
    }
//Check amount of arguments end

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
        else if (buffer == "-c" || buffer == "--config") {
            #ifdef DEBUG
            std::cout << "### Configuration config file\n";
            #endif //DEBUG
            configFileName = argv[i + 1];
            if (!findFile(configFileName)) {
                std::cout << "Invalid config file\n";
                exit(1);
            }
        }
        else {
            if (configFileName.empty()) {
                std::cout << "You must provide a config file\n";
                exit(1);
            }
        }
    }
//Configuration end

//Read config file
    try {
        configFile.open(configFileName);
        getline(configFile, buffer);
        //buffer = buffer - startAmountCand; //may throw exception const char*
        myList = new voteList(stoi(buffer - startAmountCand)); //may throw exception std::invalid_argument

        getline(configFile, buffer);
        //buffer = buffer - startAmountClients; //may throw exception const char*
        amountClients = stoi(buffer - startAmountClients); //may throw exception std::invalid_argument
        
        for(int i{}; i < myList->getAmount(); ++i) {
            getline(configFile, buffer); //may throw exception std::exception
            myList->editName(buffer, i);
            myList->editCount(i, 0);
            myList->createId(i);
        }
        configFile.close();
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "!!! Error: " << ex.what() << std::endl;
        configFile.close();
        exit(1);
    }
    catch (const char* ex) {
        std::cout << "!!! Error: " << ex << std::endl;
        configFile.close();
        exit(1);
    }
    catch (const std::exception& ex) {
        std::cout << "!!! Error: " << ex.what() << std::endl;
        configFile.close();
        delete myList;
        exit(1);
    }

//Read config file end

//Initialize socket
    try {
        socket->initializeSocket();
    }
    catch (const char* ex) {
        std::cout << "!!! Error: " << ex << std::endl;
        delete socket;
        delete myList;
        exit(1);
    }
//Initialize socket end

//Start listening and sendData
    //Data format: name@id%
    //@ - разделитель, % - разделитель записей, ^ - отправка дополнительных данных
    char** data = getDataToSend(myList, layersData);
    try {
        for (int i{}; i < amountClients * 2; ++i) {
            writeTable(myList, arrayOper[1]);
            socket->connectWithClient();
            socket->readFromSocket();
            buf = socket->getBuffer()[0];
            switch (buf) {
                case 'g':
                    if (arrayOper[0] == amountClients) socket->writeToSocket("You're fuck up!!!", 18);
                    else {
                        for (int i{}; i < layersData; i++) {
                            socket->writeToSocket(data[i], 256);
                            arrayOper[0]++;
                        }
                    }
                    break;
                case 's':
                    if (arrayOper[1] == amountClients) socket->writeToSocket("You're fuck up!!!", 18);
                    else {
                        socket->readFromSocket();
                        std::cout << "### " << socket->getBuffer() << '\n';
                        myList->addCount(atoi(socket->getBuffer()));
                        arrayOper[1]++;
                    }
                    break;
                default:
                    break;
            }
            writeTable(myList, arrayOper[1]);
        }
        delete[] data[0];
        delete[] data;
        delete socket;
        delete myList;
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "!!! Error: " << ex.what() << std::endl;
        delete[] data[0];
        delete[] data;
        delete socket;
        delete myList;
        exit(1);
    }
    return 0;
}