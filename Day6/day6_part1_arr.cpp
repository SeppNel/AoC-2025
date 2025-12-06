#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
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

int main(int argc, char *argv[]) {
    vector<string> lines = parseInput("example_input.txt");

    uint64_t total = 0;
    vector<char> operations;
    vector<vector<uint32_t>> numbers;

    {
        std::stringstream ss(*lines.end());
        char ch;

        while (ss >> ch) {
            operations.push_back(ch);
        }
    }

    for (auto it = lines.rbegin() + 1; it < lines.rend(); it++) {
        std::stringstream ss(*it);
        uint8_t count = 0;
        uint32_t num;
        while (ss >> num) {
            numbers[count].push_back(num);
            count++;
        }
    }
    std::cout << "Total = " << total << std::endl;
}