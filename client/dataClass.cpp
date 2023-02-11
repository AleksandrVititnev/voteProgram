#include "dataClass.h"
#include "globalState.h"
dataClass::dataClass(int _amount) : amount{_amount} {
    #ifdef DEBUG
    std::cout << "dataClass::dataClass Start\n";
    #endif //DEBUG

    if (_amount <= 0) throw std::invalid_argument("dataClass::dataClass amount must be greater than 0.");

    names = new std::string[amount];
    id = new std::string[amount];

    #ifdef DEBUG
    std::cout << "dataClass::dataClass End\n";
    #endif //DEBUG
}
dataClass::~dataClass() {
    #ifdef DEBUG
    std::cout << "dataClass::~dataClass\n";
    #endif //DEBUG

    delete[] names;
    delete[] id;
}
void dataClass::setName(int& index, std::string& _name) {
    #ifdef DEBUG
    std::cout << "dataClass::setName Start\n";
    #endif //DEBUG

    if (index < 0) throw std::invalid_argument("dataClass::setName index must be greater than 0.");
    else names[index] = _name;

    #ifdef DEBUG
    std::cout << "dataClass::setName End\n";
    #endif //DEBUG
    return;
}
std::string dataClass::getName(int& index) {
    if (index < 0) throw std::invalid_argument("dataClass::getName index must be greater than 0.");

    return names[index];
}
// void dataClass::setId(int& index, int _id) {
//     #ifdef DEBUG
//     std::cout << "dataClass::setId Start\n";
//     #endif //DEBUG

//     if (index < 0) throw std::invalid_argument("dataClass::setId index must be greater than 0.");
//     else id[index] = _id;

//     #ifdef DEBUG
//     std::cout << "dataClass::setId End\n";
//     #endif //DEBUG
//     return;
// }
void dataClass::setId(int& index, std::string _id) {
    #ifdef DEBUG
    std::cout << "dataClass::setId Start\n";
    #endif //DEBUG

    if (index < 0) throw std::invalid_argument("dataClass::setId index must be greater than 0.");
    else id[index] = _id;

    #ifdef DEBUG
    std::cout << "dataClass::setId End\n";
    #endif //DEBUG
    return;
}
std::string dataClass::getId(int& index) {
    if (index < 0) throw std::invalid_argument("dataClass::getid index must be greater than 0.");

    return id[index];
}
int dataClass::getAmount() const {
    return amount;
}