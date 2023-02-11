#include "myClass.h"
#include "globalState.h"
voteList::voteList(int count) : amount(count) {
    if (count <= 0) {
        throw std::invalid_argument("voteList::voteList: count must be greater than 0");
    }
    voteNames = new std::string[amount];
    voteCount = new int[amount];
    id = new int[amount];

    srand(time(NULL));

    #ifdef DEBUG
    std::cout << "### VoteList::VoteList\n";
    #endif // DEBUG
}
voteList::~voteList() {
    delete[] voteNames;
    delete[] voteCount;

    #ifdef DEBUG
    std::cout << "### VoteList::~VoteList\n";
    #endif // DEBUG
}
void voteList::createId(int index) {
    #ifdef DEBUG
    std::cout << "### voteList::createId\n";
    #endif // DEBUG
    if (index < 0) {
        throw std::invalid_argument("voteList::createId: count must be greater than 0");
    }

    id[index] = 1000 + rand() % 99999;
    return;
}
int voteList::getId(int index) {
    // #ifdef DEBUG
    // std::cout << "### voteList::getId\n";
    // #endif // DEBUG
    if (index < 0) {
        throw std::invalid_argument("voteList::getId: count must be greater than 0");
    }
    return id[index];
}
void voteList::editName(std::string& name, int index) {
    if (index < 0) {
        throw std::invalid_argument("voteList::editName: count must be greater than 0");
    }
    #ifdef DEBUG
    std::cout << "### voteList::editName\n";
    #endif // DEBUG
    voteNames[index] = name;
    return;
}
std::string voteList::getName(int index) const {
    if (index < 0) {
        throw std::invalid_argument("voteList::getName count must be greater than 0");
    }
    // #ifdef DEBUG
    // std::cout << "### voteList::getName\n";
    // #endif // DEBUG
    return voteNames[index];
}
void voteList::editCount(int index, int count) {
    if (index < 0) {
        throw std::invalid_argument("voteList::editCount index must be greater than 0");
    }
    if (count < 0) {
        throw std::invalid_argument("voteList::editCount count must be greater than 0");
    }
    #ifdef DEBUG
    std::cout << "### voteList::editCount\n";
    #endif // DEBUG
    voteCount[index] = count;
    return;
}
void voteList::addCount(int _id, int& temp) {
    if (_id <= 0) throw std::invalid_argument("voteList::addCount id must be greater than 0");

    for (int i{}; i < amount; i++) {
        if (_id == id[i]) {
            voteCount[i]++;
            temp = i;
        }
    }

    return;
}
int voteList::getCount(int index) const {
    if (index < 0) {
        throw std::invalid_argument("voteList::getCount count must be greater than 0");
    }
    // #ifdef DEBUG
    // std::cout << "### voteList::getCount\n";
    // #endif // DEBUG
    return voteCount[index];
}
int voteList::getAmount() const {
    // #ifdef DEBUG
    // std::cout << "### voteList::getAmount\n";
    // #endif // DEBUG
    return amount;
}
std::string voteList::getNote(int index) {
    if (index < 0) {
        throw std::invalid_argument("voteList::getCount count must be greater than 0");
    }
    std::string note = getName(index) + "@" + std::to_string(getId(index));
    return note;
}