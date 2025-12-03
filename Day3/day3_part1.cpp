#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

vector<string> parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
    }

    vector<string> ret;
    string line;
    while (std::getline(input, line)) {
        ret.push_back(line);
    }

    input.close();
    return ret;
}

int getPosOfMax(const string &s){
    int pos = -1;
    uint8_t max = 0;

    for (size_t i = 0; i < s.size(); i++){
        if (s[i] == '9' && i != s.size() - 1){
            return i;
        }

        uint8_t intVal = s[i] - '0';

        if (intVal > max && i != s.size() - 1){
            max = intVal;
            pos = i;
        }
    }
    
    return pos;
}

int getPosOfMax2(const string &s, uint from){
    int pos = -1;
    uint8_t max = 0;

    for (size_t i = from; i < s.size(); i++){
        if (s[i] == '9'){
            return i;
        }

        uint8_t intVal = s[i] - '0';

        if (intVal > max){
            max = intVal;
            pos = i;
        }
    }
    
    return pos;
}

int main(int argc, char *argv[]) {
    vector<string> banks = parseInput("example_input.txt");

    uint64_t total = 0;
    for (const auto &str : banks) {
        int maxPos1 = getPosOfMax(str);
        int maxPos2 = getPosOfMax2(str, maxPos1 + 1);

        string val{str[maxPos1], str[maxPos2]};
        std::cout << val << std::endl;
    }

    std::cout << "Total = " << total << std::endl;
}