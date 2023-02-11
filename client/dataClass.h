#ifndef DATACLASS_H
#define DATACLASS_H
#include <iostream>
#include <cstring>

class dataClass {
    std::string* names;
    //int* id;
    std::string* id;
    int amount;
public:
    dataClass() = default;
    dataClass(int);
    ~dataClass();
    void setName(int&, std::string&);
    std::string getName(int&);
    void setId(int&, std::string);
    std::string getId(int&);
    int getAmount() const;
};
#endif // DATACLASS_H