#include "logClass.h"
logger::logger() {
    file.open("log/" + getDate() + "@" + getTime(5) + ".txt");
}
logger::~logger() {
    file.close();
}
std::string logger::getTime() {
    system("date +%H:%M > temp");
    std::ifstream temp("temp");
    std::string result;
    getline(temp, result);
    temp.close();
    system("rm temp");
    return result;
}
std::string logger::getTime(int) {
    system("date +%H_%M > temp");
    std::ifstream temp("temp");
    std::string result;
    getline(temp, result);
    temp.close();
    system("rm temp");
    return result;
}
std::string logger::getDate() {
    system("date +%u_%m_%Y > temp");
    std::ifstream temp("temp");
    std::string result;
    getline(temp, result);
    temp.close();
    system("rm temp");
    return result;
}
void logger::logVote(voteList* myList, int index) {
    buffer = getTime() + " ### Голос за " + myList->getName(index) + " " + std::to_string(myList->getCount(index)) + "\n";
    //file << "###" << "Голос за " << myList->getName(index) << " " << myList->getCount(index);
    //file << '\n';
    file << buffer;
    return;
}
void logger::logResult(voteList* myList, int index) {
    buffer = getTime() + " ### Голосование выиграл: " + myList->getName(index) + "\n";
    //file << "###" << "Голосование выиграл: " << myList->getName(index) << '\n';
    file << buffer;
    return;
}
void logger::logChar(const char* str) {
    buffer = getTime() + " ### " + str + "\n";
    file << buffer;
    return;
}
void logger::logStr(std::string str) {
    buffer = getTime() + " ### " + str + "\n";
    file << buffer;
    return;
}