#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

inline uint64_t pow10u(const int n) {
    static const uint64_t p10[20] = {
        1ULL, 10ULL, 100ULL, 1000ULL, 10000ULL, 100000ULL, 1000000ULL,
        10000000ULL, 100000000ULL, 1000000000ULL, 10000000000ULL,
        100000000000ULL, 1000000000000ULL, 10000000000000ULL,
        100000000000000ULL, 1000000000000000ULL,
        10000000000000000ULL, 100000000000000000ULL,
        1000000000000000000ULL, 10000000000000000000ULL};
    return p10[n];
}

struct Range {
    uint64_t start;
    uint64_t end;
};

std::vector<Range> parseInput(const std::string &path) {
    std::ifstream input(path);
    if (!input) {
        std::cerr << "Unable to open file " << path << "\n";
        return {};
    }

    std::vector<Range> ranges;
    uint64_t a, b;
    char dash, comma;

    while (input >> a >> dash >> b) {
        ranges.emplace_back(a, b);
        input >> comma;
    }
    return ranges;
}

int main(int argc, char *argv[]) {
    vector<Range> ranges = parseInput("input.txt");

    uint64_t total = 0;
    for (const auto &range : ranges) {
        for (uint64_t i = range.start; i <= range.end; i++) {

            int len = 0;
            for (uint64_t t = i; t > 0; t /= 10)
                len++;

            bool valid = true;
            for (size_t j = 1; j <= len / 2; j++) {
                if (len % j != 0) {
                    continue;
                }

                uint64_t window = i / pow10u(len - j);
                bool window_valid = false;
                uint64_t copy = i;
                uint64_t pow10j = pow10u(j);

                for (int k = len; k > 0; k -= j) {
                    if (copy % pow10j != window) {
                        window_valid = true;
                        break;
                    }
                    copy /= pow10j;
                }

                if (!window_valid) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                total += i;
            }
        }
    }

    std::cout << "Total = " << total << std::endl;
}