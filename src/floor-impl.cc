module floor;

bool Floor::validSpawn(int x, int y) {
    return grid[y][x] == '.' && enemies[y][x] == nullptr;
}