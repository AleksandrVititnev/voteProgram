#include "additionalFunctions.h"
#include "globalState.h"
bool isStartOfString(std::string str, std::string strStart) {
    bool ans = false;
    if (str.length() < strStart.length()) return ans;
    for (size_t i{}; i < strStart.length(); i++) {
        if (str[i] == strStart[i]) ans = true;
        else {
            ans = false;
            break;
        }
    }
    return ans;
}

std::string operator-(std::string first, std::string second) {
    if (!isStartOfString(first, second)) throw "strStart is not start of string";
    char* newChar = new char[first.size() - second.size()];
    for (size_t i{}; i < (first.size() - second.size()); i++) {
        newChar[i] = first[i + second.size()];
    }
    std::string newStr(newChar);
    delete[] newChar;
    return newStr;
}

char** getDataToSend(voteList* myList, int& layersData) {
    //Data format: name@id%
    //@ - разделитель, % - разделитель записей, ^ - отправка дополнительных данных
    char** data;
    int lenAllData = 0, amountPieceData = 1;
    int signOnWrite = 0;
    std::string buffer;
    for (int i{}; i < myList->getAmount(); ++i) {
        lenAllData += myList->getName(i).length();
        lenAllData++;
        lenAllData += std::to_string(myList->getId(i)).length();
        lenAllData++;
    }
    if (lenAllData > 255) {
        amountPieceData = lenAllData / 255 + 1;
        lenAllData += amountPieceData - 1;
    }
    layersData = amountPieceData;
    data = new char*[amountPieceData];
    for (int i{}; i < amountPieceData; ++i) {
        data[i] = new char[256];
        bzero(data[i], 256);
    }
    if (lenAllData > 255) {
        for (int i{}; i < amountPieceData - 1; ++i) {
            data[i][0] = '^';
        }
        signOnWrite = 1;
    }
    // for(int amountChar{signOnWrite}, layer{}, numberCand{}; amountChar < lenAllData; ++amountChar) {
    //     if (amountPieceData > 1 && amountChar % )
    // }
    #ifdef DEBUG
    std::cout << "### getDataToSend1\n";
    #endif // DEBUG
    for (int layer{}, nowChar{signOnWrite}, numCand{}; layer < amountPieceData && numCand < myList->getAmount();) {
        if (nowChar == 255) {
            data[layer][256] = '\0';
            layer++;
            if (layer == amountPieceData - 1) signOnWrite = 0;
            nowChar = signOnWrite;
        }
        buffer = myList->getNote(numCand);
        for (size_t i{}; i < buffer.length(); i++) {
            data[layer][nowChar] = buffer[i];
            if (nowChar == 255) {
                data[layer][256] = '\0';
                layer++;
                if (layer == amountPieceData - 1) signOnWrite = 0;
                nowChar = signOnWrite;
            }
            else nowChar++;
        }
        if (numCand == myList->getAmount() - 1) {
            data[layer][nowChar] = '#';
            nowChar++;
        }
        else {
            data[layer][nowChar] = '%';
            nowChar++;
        }
        numCand++;
    }
    data[amountPieceData - 1][256] = '\0';
    #ifdef DEBUG
    std::cout << "### getDataToSend2\n";
    #endif // DEBUG
    return data;
}
void writeTable(voteList* myList, int voted) {
    #ifndef DEBUG
    system("clear");
    #endif //DEBUG
    #ifdef DEBUG
    std::cout << "You're in DEBUG mode\n";
    #endif //DEBUG
    system("date");
    std::cout << "Проводится голосование:\n";
    std::cout << "Проголосовало: " << voted << " человек.\n";
    std::cout << "Текущая статистика:\n";
    for (int i{}; i < myList->getAmount(); ++i) {
        std::cout << "За " << myList->getName(i) << " проголосовало: " << myList->getCount(i) << '\n';
    }
    return;
}
std::string toUpperCase(const std::string& str) {
    std::string ans = str;
    for (int i{}; i < str.length(); i++) {
        ans[i] = toupper(str[i]);
    }
    return ans;
}