module chamber;
import random;
import <optional>;
import <span>;
import <iostream>;

Chamber::Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]) {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            occupancy[i][j] = other[i][j];

            if (occupancy[i][j]) {
                emptyCells.emplace(j, i);
            }
        }
    }
};

bool Chamber::contains(int x, int y) const {
    return occupancy[y][x];
}

void Chamber::removeEmpty(int x, int y) {
    emptyCells.erase({x, y});
}

std::optional<std::pair<std::pair<int, int>, constants::Direction>> Chamber::randomHoard() const {
    std::vector<std::pair<std::pair<int, int>, std::vector<constants::Direction>>> res;

    for (const auto& cell : emptyCells) {
        std::vector<constants::Direction> validDirs;

        for (int d = 0; d < constants::NUM_DIRECTIONS; d++) {
            constants::Direction dir = static_cast<constants::Direction>(d);

            if (emptyCells.contains(cell + dir)) {
                validDirs.push_back(dir);
            }
        }
        if (validDirs.size() > 0) {
            res.push_back({cell, validDirs});
        }
    }

    if (res.size() == 0) {
        return std::nullopt;
    }


    int rCell = randomNum(0, static_cast<int>(res.size()) - 1);
    int rDir = randomNum(0, static_cast<int>(res[rCell].second.size()) - 1);

    return {{res[rCell].first, res[rCell].second[rDir]}};
}

std::optional<std::pair<int, int>> Chamber::randomEmptyCell() const {
    if (emptyCells.empty()) return std::nullopt; // not enough empty cells
    int cellIdx = randomNum(0, static_cast<int>(emptyCells.size()) - 1);
    auto it = emptyCells.begin();

    for (int i = 0; i < cellIdx; i++) {
        it++;
    }

    return *it;
}
