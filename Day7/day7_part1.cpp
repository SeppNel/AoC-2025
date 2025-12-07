#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

using std::string, std::vector;

typedef std::pair<uint32_t, uint32_t> Coord;

vector<vector<char>> parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<char>> ret;

    string line;
    while (std::getline(input, line)) {
        vector<char> line_vec;
        line_vec.insert(line_vec.begin(), line.begin(), line.end());
        ret.push_back(line_vec);
    }

    input.close();
    return ret;
}

std::pair<uint32_t, uint32_t> findStart(const vector<vector<char>> &grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                return {i, j};
            }
        }
    }

    return {0, 0};
}

uint64_t countSplits(const vector<vector<char>> &grid) {
    uint64_t count = 0;
    for (size_t i = 1; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^' && grid[i - 1][j] == '|') {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    vector<vector<char>> grid = parseInput("input.txt");

    Coord start = findStart(grid);

    std::queue<Coord> to_check;
    to_check.push(start);

    while (!to_check.empty()) {
        Coord current = to_check.front();
        current.first++;
        if (current.first >= grid.size()) {
            to_check.pop();
            continue;
        }

        while (grid[current.first][current.second] == '.') {
            grid[current.first][current.second] = '|';
            current.first++;
            if (current.first == grid.size()) {
                break;
            }
        }

        if (current.first == grid.size()) {
            to_check.pop();
            continue;
        }

        if (grid[current.first][current.second] == '^') {
            if (current.second > 0) {
                to_check.push({current.first, current.second - 1});
            }
            if (current.second < grid[0].size() - 1) {
                to_check.push({current.first, current.second + 1});
            }
        }
        to_check.pop();
    }

    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[0].size(); j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "Total = " << countSplits(grid) << std::endl;
}