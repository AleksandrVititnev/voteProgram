#ifndef MYCLASS_H
#define MYCLASS_H
#include <iostream>
#include <memory>
#include <cstring>
#include <exception>
#include <ctime>
#include <cstdlib>
class voteList {
private:
    int amount = 0;
    std::string* voteNames{nullptr};
    int* voteCount{nullptr};
    int* id{nullptr};
public:
    voteList() = default;
    voteList(int);
    ~voteList();
    void createId(int);
    int getId(int);
    void editName(std::string&, int);
    std::string getName(int) const;
    void editCount(int, int);
    void addCount(int, int&);
    int getCount(int) const;
    int getAmount() const;
    std::string getNote(int);
};
#endif //MYCLASS_H