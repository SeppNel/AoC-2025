#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define START 50
#define LIMIT 100

using std::string, std::vector;
typedef vector<std::pair<char, uint16_t>> instructions_t;

instructions_t parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
    }

    instructions_t ret;
    std::string line;
    while (std::getline(input, line)) {
        char dir = line[0];
        line = line.substr(1);
        uint value = std::stoul(line);

        ret.emplace_back(dir, value);
    }

    input.close();
    return ret;
}

int main(int argc, char *argv[]) {
    instructions_t instructions = parseInput("input.txt");

    uint64_t total = 0;
    int32_t pos = START;
    for (const auto &i : instructions) {
        if (i.first == 'R') {
            pos += i.second;
            total += pos / LIMIT;
            pos %= LIMIT;
        } else {
            bool prevPos = pos; // If pos == 0, dont add one to total
            pos -= i.second;
            if (pos <= 0) {
                total += (uint)prevPos + abs(pos) / LIMIT;
            }
            pos = ((pos % LIMIT) + LIMIT) % LIMIT;
        }
    }

    std::cout << "Total = " << total << std::endl;
}