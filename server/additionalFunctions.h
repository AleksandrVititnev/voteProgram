#ifndef ADDFUNC_H
#define ADDFUNC_H
#include <cstring>
#include <exception>
#include "myClass.h"
bool isStartOfString(std::string, std::string);
std::string operator-(std::string, std::string);
char** getDataToSend(voteList*, int&);
void writeTable(voteList*, int);
std::string toUpperCase(const std::string&);
#endif //ADDFUNC_H