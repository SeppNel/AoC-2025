#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define LEN 12

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

int getPosOfMax(const string &s, const uint8_t from, const uint8_t iter) {
    int pos = -1;
    uint8_t max = 0;

    for (size_t i = from; i < s.size() - (LEN - iter); i++) {
        if (s[i] == '9') {
            return i;
        }

        uint8_t intVal = s[i] - '0';
        if (intVal > max) {
            max = intVal;
            pos = i;
        }
    }

    return pos;
}

int main(int argc, char *argv[]) {
    vector<string> banks = parseInput("input.txt");

    uint64_t total = 0;
    for (const auto &str : banks) {
        uint8_t from = 0;
        string value = "";
        for (size_t i = 1; i <= LEN; i++) {
            int maxPos = getPosOfMax(str, from, i);
            value += str[maxPos];
            from = maxPos + 1;
        }
        total += stoull(value);
    }

    std::cout << "Total = " << total << std::endl;
}