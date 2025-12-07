#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
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

Coord findStart(const vector<vector<char>> &grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                return {i, j};
            }
        }
    }

    return {0, 0};
}

uint64_t timelines[142][141] = {0};
uint64_t getTimelines(uint32_t r, uint32_t c, const vector<vector<char>> &grid) {
    if (timelines[r][c] != 0) {
        return timelines[r][c];
    }
    if (r == grid.size() - 1) {
        timelines[r][c] = 1;
        return 1;
    }
    uint64_t res = 0;
    if (grid[r + 1][c] == '.') {
        res = getTimelines(r + 1, c, grid);
    }
    if (grid[r + 1][c] == '^') {
        // col doesn't have to be bounds checked
        // as the input is designed so that beams never go off the sides
        res = getTimelines(r + 1, c - 1, grid) + getTimelines(r + 1, c + 1, grid);
    }
    timelines[r][c] = res;
    return res;
}

int main(int argc, char *argv[]) {
    vector<vector<char>> grid = parseInput("input.txt");

    Coord start = findStart(grid);

    std::cout << "Total = " << getTimelines(start.first, start.second, grid) << std::endl;
}