#include "header.h"
#include "sockClass.h"
#include "myClass.h"
#include "findFile.h"
#include "additionalFunctions.h"
#include "globalState.h"
#include "logClass.h"

//./App -p or --port 25566 -c or --config file.txt
int main(int argc, char** argv) {
//Variables
    int temp = 0, amountClients = 0, layersData = 0;
    int arrayOper[2] = {0, 0};
    std::string buffer, configFileName;
    std::string startAmountCand("amountCand="), startAmountClients("amountClients=");
    char buf;
    bool isDraw = false;
    voteList* myList;
    mySocket* socket;
    logger lg;
    std::ifstream configFile;
    configFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//Variables end

//Check amount of arguments
    
    
    for (int i{1}; i < argc; i++) {
        buffer = argv[i];
        if (buffer == "-h" or buffer == "--help") {
            std::cout << "Use programm with:\n";
            std::cout << "-p port - server's port.\n";
            std::cout << "-i IP - server's IP address.\n";
            std::cout << "Config file must have:\n";
            std::cout << "amountCand=number - amount candidats.\n";
            std::cout << "amountClients=number - amount clients.\n";
            std::cout << "Next strings - candidates names.\n";
            exit(1);
        }
    }
    if (argc <= 4 || argc > 5) {
        std::cout << "Invalid arguments\n Input: -h or --help\n";
        exit(1);
    }
//Check amount of arguments end

    lg.logStr("Start programm");

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
                socket = new mySocket(temp, lg);
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
                if (socket) delete[] socket;
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

//Edit data
    try {
        std::cout << "Do you want to see or edit data? Y or N ";
        std::getline(std::cin, buffer);
        if (std::cin.good() and (toUpperCase(buffer) == "YES" or toUpperCase(buffer) == "Y")) {
            std::cout << "Data:\n";
            std::cout << "Amount clients: " << amountClients << '\n';
            std::cout << "Amount candidats: " << myList->getAmount() << '\n';
            for (int i{}; i < myList->getAmount(); i++) {
                std::cout << "№ " << i + 1 << " name: " << myList->getName(i) << " id: " << myList->getId(i) << '\n';
            }
            while(true) {
                std::cout << "Which note do you want to edit? Enter number or q for exit.\n";
                std::getline(std::cin, buffer);
                if (toUpperCase(buffer) == "QUIT" or toUpperCase(buffer) == "Q" or toUpperCase(buffer) == "EXIT") break;
                else if (isdigit(buffer[0])) {
                    temp = stoi(buffer);
                    if (temp > myList->getAmount() or temp <= 0) std::cout << "Incorrect number!\n";
                    else {
                        std::cout << "Enter name: ";
                        std::getline(std::cin, buffer);
                        if (!buffer.empty()) myList->editName(buffer, temp - 1);
                    }
                }
            }
        }
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "!!! Error: " << ex.what() << std::endl;
        delete socket;
        delete myList;
        exit(1);
    }
    catch (const char* ex) {
        std::cerr << "Error: " << ex << std::endl;
        delete myList;
        delete socket;
        exit(1);
    }
//Edit data end

//Start listening, sendData, getData
    //Data format: name@id%
    //@ - разделитель, % - разделитель записей, ^ - отправка дополнительных данных
    char** data = getDataToSend(myList, layersData);
    socket->initializeSocket();
    lg.logChar("Start vote.");
    try {
        for (int i{}; i < amountClients * 2; ++i) {
            writeTable(myList, arrayOper[1]);
            socket->connectWithClient();
            socket->readFromSocket();
            buf = socket->getBuffer()[0];
            switch (buf) {
                case 'g':
                    for (int i{}; i < layersData; i++) {
                        socket->writeToSocket(data[i], 256);
                        arrayOper[0]++;
                    }
                    break;
                case 's':
                    if (arrayOper[1] == amountClients) socket->writeToSocket("You're fuck up!!!", 18);
                    else {
                        //socket->readFromSocket();
                        while (true) {
                            socket->readFromSocket();
                            #ifdef DEBUG
                            std::cout << "###################" << socket->getBuffer() << '\n';
                            #endif //DEBUG
                            if (atoi(socket->getBuffer()) <= 0) {
                                socket->writeToSocket("e", 2);
                            }
                            else {
                                socket->writeToSocket("o", 2);
                                break;
                            }
                        }
                        myList->addCount(atoi(socket->getBuffer()), temp);
                        lg.logVote(myList, temp);
                        arrayOper[1]++;
                    }
                    break;
                default:
                    break;
            }
            writeTable(myList, arrayOper[1]);
        }
        for (int i{}; i < layersData; i++) {
            delete[] data[i];
        }
        delete[] data;
        delete socket;
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "!!! Error: " << ex.what() << std::endl;
        for (int i{}; i < layersData; i++) {
            delete[] data[i];
        }
        delete[] data;
        delete socket;
        delete myList;
        exit(1);
    }
    catch (const char* ex) {
        std::cerr << "Error: " << ex << std::endl;
        for (int i{}; i < layersData; i++) {
            delete[] data[i];
        }
        delete[] data;
        delete myList;
        delete socket;
        exit(1);
    }
//Start listening, sendData, getData

//Statistics
    try {
        #ifndef DEBUG
        system("clear");
        #endif //DEBUG

        temp = 0;
        for (int i{}; i < myList->getAmount(); i++) {
            if (myList->getCount(i) > myList->getCount(temp)) {
                temp = i;
                isDraw = false;
            }
            if (myList->getCount(i) == myList->getCount(temp) && i != temp) {
                isDraw = true;
                temp = i;
            } 
        }
        std::cout << "Результаты голосования: " << '\n';
        if (!isDraw) {
            std::cout << "Выиграл: " << myList->getName(temp) << " с кол-вом голосов: " << myList->getCount(temp) << '\n';
            buffer = "Выиграл: " + myList->getName(temp) + " с кол-вом голосов: " + std::to_string(myList->getCount(temp));
            lg.logStr(buffer);
        }
        if (isDraw) {
            std::cout << "Среди кандидатов есть ничья.\n";
            lg.logChar("Среди кандидатов есть ничья.");
        }
        lg.logChar("Конец голосования.");
    }
    catch (const char* ex) {
        std::cout << "Error: " << ex << std::endl;
        delete[] data;
        delete myList;
        delete socket;
        exit(1);
    }
    delete myList;
    return 0;
}