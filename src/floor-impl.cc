module floor;

bool Floor::validSpawn(int x, int y) {
    return grid[y][x] == '.' && gold[y][x] == nullptr && potions[y][x] == nullptr;
}

Floor::Floor() {}