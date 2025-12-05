#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

struct Range {
    uint64_t from;
    uint64_t to;
};

vector<Range> parseInput(string path) {
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

    input.close();
    return ret;
}

void mergeRanges(vector<Range> &ranges) {
    for (size_t i = 0; i < ranges.size(); i++) {
        const Range &a = ranges[i];
        for (size_t j = 0; j < ranges.size(); j++) {
            if (i == j) {
                continue;
            }
            const Range &b = ranges[j];

            if ((a.to == 0 && a.from == 0) || (b.from == 0 && b.to == 0)) {
                continue;
            }

            if (a.from >= b.from && a.from <= b.to && a.to > b.to) {
                ranges[j].to = a.to;
                ranges[i].to = 0;
                ranges[i].from = 0;
            } else if (a.to >= b.from && a.to <= b.to && a.from < b.from) {
                ranges[j].from = a.from;
                ranges[i].to = 0;
                ranges[i].from = 0;
            } else if (a.from >= b.from && a.to <= b.to) {
                ranges[i].from = 0;
                ranges[i].to = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    vector<Range> ranges = parseInput("input.txt");

    mergeRanges(ranges);

    uint64_t total = 0;
    for (const auto &range : ranges) {
        if (range.to == 0 && range.from == 0) {
            continue;
        }
        total += range.to - range.from + 1;
    }
    std::cout << "Total = " << total << std::endl;
}