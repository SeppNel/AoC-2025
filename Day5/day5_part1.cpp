#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>

using std::string, std::vector;

struct Range {
    uint64_t from;
    uint64_t to;
};

vector<Range> parseInput(string path, vector<uint64_t> &ingredients) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
    }

    vector<Range> ret;

    string line;
    while (std::getline(input, line)) {
        if (line == "") {
            break;
        }
        uint8_t dash_pos = line.find("-");

        string num1 = line.substr(0, dash_pos);
        string num2 = line.substr(dash_pos + 1);

        ret.emplace_back(static_cast<uint64_t>(std::stoull(num1)), static_cast<uint64_t>(std::stoull(num2)));
    }

    while (std::getline(input, line)) {
        uint64_t n = std::stoull(line);
        ingredients.push_back(n);
    }

    input.close();
    return ret;
}

int main(int argc, char *argv[]) {
    vector<uint64_t> ingredients;
    vector<Range> ranges = parseInput("input.txt", ingredients);

    uint64_t total = 0;
    for (const auto &id : ingredients) {
        for (const auto &range : ranges) {
            if (id >= range.from && id <= range.to) {
                total++;
                break;
            }
        }
    }
    std::cout << "Total = " << total << std::endl;
}