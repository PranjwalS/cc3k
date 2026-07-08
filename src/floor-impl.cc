module floor;

using namespace constants;

Floor::Floor() {
    for (int i = 0; i < board::HEIGHT; i++) {
        for (int j = 0; j < board::WIDTH; j++) {
            grid[i][j] = constants::EMPTY_FLOOR[i * board::WIDTH + j];
        }
    }
}

bool Floor::validSpawn(int x, int y) {
    return grid[y][x] == '.' && gold[y][x] == nullptr && potions[y][x] == nullptr;
}

