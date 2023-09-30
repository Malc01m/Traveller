#include "StringTools.h"

std::string StringTools::strVectToNewlines(std::vector<std::string> vect) {
    std::string str;
    for (unsigned int i = 0; i < vect.size(); i++) {
        str.append(vect.at(i) + "\n");
    }
    return str;
}