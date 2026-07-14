module chamber;
import random;

bool Chamber::contains(int x, int y) {
    return occupancy[y][x];
}

std::optional<std::pair<int, int>> Chamber::randomEmptyCell() const {
    if (emptyCells.empty()) return std::nullopt; // not enough empty cells
    int cellIdx = randomNum(0, static_cast<int>(emptyCells.size()) - 1);
    return emptyCells.at(cellIdx);
}
