#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string, std::vector;

vector<string> parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
        exit(EXIT_FAILURE);
    }

    vector<string> ret;

    string line;
    while (std::getline(input, line)) {
        ret.push_back(line);
    }

    string last = ret[ret.size() - 1];

    ret.erase(ret.end() - 1);
    ret.insert(ret.begin(), last);

    input.close();

    return ret;
}

int main(int argc, char *argv[]) {
    vector<string> lines = parseInput("input.txt");

    uint64_t total = 0;
    vector<char> operations;
    {
        std::stringstream ss(*lines.begin());
        char ch;

        while (ss >> ch) {
            operations.push_back(ch);
        }
    }

    vector<uint64_t> numbers;
    for (const char ch : operations) {
        if (ch == '+') {
            numbers.push_back(0);
        } else {
            numbers.push_back(1);
        }
    }
    int64_t number_idx = -1;

    char operation;
    for (uint32_t col = 0; col < lines[0].size(); col++) {
        string str = "";
        for (uint8_t row = 0; row < lines.size(); row++) {
            char c = lines[row][col];
            if (c == ' ') {
                continue;
            } else if (c == '+' || c == '*') {
                operation = c;
                number_idx++;
                continue;
            } else {
                str += c;
            }
        }
        if (str != "") {
            uint64_t val = stoull(str);
            if (operation == '+') {
                numbers[number_idx] += val;
            } else {
                numbers[number_idx] *= val;
            }
        }
    }

    for (const auto n : numbers) {
        total += n;
    }

    std::cout << "Total = " << total << std::endl;
}