#include "findFile.h"
bool findFile(std::string nameFile) {
    bool ans = false;
    std::string findInquiry = "if test -f " + nameFile + "; then echo 1; else echo 0; fi > temp";
    system(findInquiry.c_str());
    std::ifstream temp("temp");
    temp >> ans;
    temp.close();
    system("rm temp");
    return ans;
}