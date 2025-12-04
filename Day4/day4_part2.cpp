#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// #define LINE_SIZE 12 // Example
#define LINE_SIZE 142
#define MAX_NEIGHBOURS 4

using std::string, std::vector;

typedef vector<vector<char>> Grid_t;

Grid_t parseInput(string path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cout << "Unable to open file " << path << std::endl;
    }

    vector<char> empty(LINE_SIZE, '.');
    Grid_t ret;
    ret.push_back(empty);

    string line;
    while (std::getline(input, line)) {
        vector<char> line_vec;
        line_vec.reserve(LINE_SIZE);
        line_vec.push_back('.');
        line_vec.insert(line_vec.end(), line.begin(), line.end());
        line_vec.push_back('.');

        ret.push_back(line_vec);
    }

    ret.push_back(empty);

    input.close();
    return ret;
}

uint32_t neighbours(const Grid_t &grid, uint32_t x, uint32_t y) {
    uint32_t count = 0;
    for (uint32_t i = x - 1; i <= x + 1; i++) {
        for (uint32_t j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }

            if (grid[i][j] == '@') {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    Grid_t grid = parseInput("input.txt");

    uint64_t total = 0;
    bool go_on = true;
    while (go_on) {
        Grid_t local_grid = grid;
        uint32_t local_total = 0;
        for (size_t i = 1; i < grid.size() - 1; i++) {
            for (size_t j = 1; j < grid[0].size() - 1; j++) {
                if (local_grid[i][j] == '@') {
                    uint32_t n = neighbours(local_grid, i, j);
                    if (n < MAX_NEIGHBOURS) {
                        local_total++;
                        grid[i][j] = '.';
                    }
                }
            }
        }

        total += local_total;
        go_on = local_total;
    }
    std::cout << "Total = " << total << std::endl;
}