module chamber;
import random;
import generation;
import <span>;

Chamber::Chamber(const int chamberNum, const Generation& generation) {
    const auto& cells = generation.getChamberPoints(chamberNum);
    addSpawnableCells(cells);
}

Chamber::Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]) {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            occupancy[i][j] = other[i][j];
            if (occupancy[i][j]) {
                occupiedCells.emplace_back(j, i);
            } else {
                emptyCells.emplace_back(j, i);
            }
        }
    }
};

bool Chamber::contains(int x, int y) const {
    return occupancy[y][x];
}

void Chamber::refreshEmptyCells() {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            if (!occupancy[i][j]) {
                emptyCells.emplace_back(j, i);
            }
        }
    }
}

void Chamber::addSpawnableCells(std::span<const std::pair<int, int>> cells) {
    for (const auto& [x, y] : cells) {
        if (!occupancy[y][x]) {
            occupancy[y][x] = true;
            occupiedCells.emplace_back(x, y);
        }
    }
    refreshEmptyCells();
}

std::optional<std::pair<int, int>> Chamber::randomEmptyCell() const {
    if (emptyCells.empty()) return std::nullopt; // not enough empty cells
    int cellIdx = randomNum(0, static_cast<int>(emptyCells.size()) - 1);
    return emptyCells.at(cellIdx);
}
