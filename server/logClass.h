#ifndef LOGCLASS_H
#define LOGCLASS_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "myClass.h"
class logger {
    std::ofstream file;
    std::string buffer;
public:
    logger();
    ~logger();
    std::string getTime();
    std::string getTime(int);
    std::string getDate();
    void logVote(voteList* myList, int index);
    void logResult(voteList* myList, int index);
    void logChar(const char* str);
    void logStr(std::string str);
};
#endif // LOGCLASS_H