module floor;

import constants;

Floor::Floor() {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            grid[i][j] = constants::EMPTY_FLOOR[i * constants::board::WIDTH + j];
            enemiesIndex[i][j] = -1;
            goldIndex[i][j] = -1;
            potionsIndex[i][j] = -1;
        }
    }
    for (int i = 0; i < constants::board::NUM_CHAMBERS; ++i) chambers[i] = nullptr;
}

bool Floor::validSpawn(int x, int y) {
    return grid[y][x] == '.' && goldIndex[y][x] == -1 && potionsIndex[y][x] == -1;
}

void Floor::addEnemy(int x, int y, int index, constants::Enemy race) {
    enemiesIndex[y][x] = index;
    grid[y][x] = static_cast<char>(race);
}

void Floor::removeEnemy(int x, int y) {
    enemiesIndex[y][x] = -1;
    grid[y][x] = '.';
}

void Floor::moveEnemy(int px, int py, int nx, int ny) {
    enemiesIndex[ny][nx] = enemiesIndex[py][px];
    grid[ny][nx] = grid[py][px];
    removeEnemy(px, py);
}

void Floor::addPotion(int x, int y, int index) {
    potionsIndex[y][x] = index;
    grid[y][x] = 'P';
}

void Floor::removePotion(int x, int y) {
    potionsIndex[y][x] = -1;
    grid[y][x] = '.';
}

void Floor::addGold(int x, int y, int index) {
    goldIndex[y][x] = index;
    grid[y][x] = 'G';
}

void Floor::removeGold(int x, int y) {
    goldIndex[y][x] = -1;
    grid[y][x] = '.';
}
