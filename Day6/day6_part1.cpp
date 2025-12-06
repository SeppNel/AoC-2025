#include <cstdint>
#include <cstdlib>
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
        exit(EXIT_FAILURE);
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
    vector<string> lines = parseInput("input.txt");

    uint64_t total = 0;
    vector<char> operations;

    {
        std::stringstream ss(*(lines.end() - 1));
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

    for (auto it = lines.rbegin() + 1; it < lines.rend(); it++) {
        std::stringstream ss(*it);
        uint32_t count = 0;
        uint64_t num;
        while (ss >> num) {
            if (operations[count] == '+') {
                numbers[count] += num;
            } else {
                numbers[count] *= num;
            }

            count++;
        }
    }

    for (const auto n : numbers) {
        total += n;
    }

    std::cout << "Total = " << total << std::endl;
}