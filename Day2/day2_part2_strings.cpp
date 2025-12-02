#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string, std::vector;

template <typename T>
inline bool inVector(const vector<T> &v, const T n) {
    for (const auto &v0 : v) {
        if (v0 == n) {
            return true;
        }
    }

    return false;
}

struct Range {
    uint64_t start;
    uint64_t end;
};

vector<Range> parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
    }

    vector<Range> ret;

    vector<char> start_vec;
    vector<char> end_vec;
    bool start = true;
    char ch;
    while (input.get(ch)) {
        if (ch == '-') {
            start = false;
        } else if (ch == ',') {
            string start_str = string(start_vec.begin(), start_vec.end());
            string end_str = string(end_vec.begin(), end_vec.end());
            ret.emplace_back(std::stoull(start_str), std::stoull(end_str));

            start = true;
            start_vec.clear();
            end_vec.clear();
        } else {
            if (start) {
                start_vec.push_back(ch);
            } else {
                end_vec.push_back(ch);
            }
        }
    }

    string start_str = string(start_vec.begin(), start_vec.end());
    string end_str = string(end_vec.begin(), end_vec.end());
    ret.emplace_back(std::stoull(start_str), std::stoull(end_str));

    input.close();
    return ret;
}

int main(int argc, char *argv[]) {
    vector<Range> ranges = parseInput("input.txt");

    uint64_t total = 0;
    for (const auto &range : ranges) {
        for (uint64_t i = range.start; i <= range.end; i++) {
            string val_str = std::to_string(i);

            bool valid = true;
            for (size_t j = 1; j <= val_str.size() / 2; j++) {
                if (val_str.size() % j != 0) {
                    continue;
                }

                string window = val_str.substr(0, j);

                bool window_valid = false;
                string copy = val_str;
                while (copy.size() >= j) {
                    string to_check = copy.substr(0, j);
                    if (window != to_check) {
                        window_valid = true;
                        break;
                    }

                    copy = copy.substr(j);
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