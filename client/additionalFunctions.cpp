#include "additionalFunctions.h"
#include "globalState.h"
void copyChar(char* from, char* to, int len) {
    for (int i{}; i < len; i++) to[i] = from[i];
    return;
}

int getAmountCand(char** const data, int& amountLayers) {
    int amountCand = 0;
    for (int i{}; i < amountLayers; i++) {
        for (int j{}; j < 256; j++) if (data[i][j] == '@') amountCand++;
    }
    return amountCand;
}

void fillList(char** const data, int& amountLayers, dataClass* myList) {
    std::string buffer;
    char buf[256];
    int temp, nowCharData = 0, nowCand = 0, amountCand, nowCharBuf = 0;

    amountCand = getAmountCand(data, amountLayers);
    bzero(buf, 256);
    for (int i{}; i < amountLayers; i++) {
        nowCharData = 0;
        if (data[i][0] == '^') nowCharData = 1;
        while (nowCharData <= 255 && nowCand < amountCand) {
            if (data[i][nowCharData] == '\0') nowCharData++;
            if (nowCharData >= 255) break;
            if (data[i][nowCharData] == '@') {
                buffer = buf;
                myList->setName(nowCand, buffer);
                bzero(buf, 256);
                buffer.clear();
                nowCharBuf = 0;
                nowCharData++;
                continue;
            }
            if (data[i][nowCharData] == '%' || data[i][nowCharData] == '#') {
                //temp = atoi(buf);
                buffer = buf;
                myList->setId(nowCand, buffer);
                if (data[i][nowCharData] == '#') break;
                bzero(buf, 256);
                buffer.clear();
                nowCharBuf = 0;
                nowCand++;
                nowCharData++;
                continue;
            }
            buf[nowCharBuf] = data[i][nowCharData];
            nowCharData++;
            nowCharBuf++;
        }
        if (nowCand == amountCand) break;
        if (data[i][nowCharData] == '#') break;
    }
    return;
}