module floor;

import constants;
import <string>;

Floor::Floor() {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            grid[i][j] = constants::EMPTY_FLOOR[i * constants::board::WIDTH + j];
            enemiesIndex[i][j] = -1;
            goldIndex[i][j] = -1;
            potionsIndex[i][j] = -1;
        }
    }

    initChambers();
}

void expand(std::string &emptyBoard, int x, int y,
            bool (&cells)[constants::board::HEIGHT][constants::board::WIDTH]) {
    auto n = std::pair{x, y} + constants::Direction::NO;
    auto e = std::pair{x, y} + constants::Direction::EA;
    auto s = std::pair{x, y} + constants::Direction::SO;
    auto w = std::pair{x, y} + constants::Direction::WE;
    
    for (auto [nx, ny] : {n, e, s, w}) {
        if (constants::board::isInBounds({nx, ny}) && emptyBoard[ny * constants::board::WIDTH + nx] == '.') {
            cells[ny][nx] = true;
            emptyBoard[ny * constants::board::WIDTH + nx] = 'x';
            expand(emptyBoard, nx, ny, cells);
        }
    }
}

void Floor::initChambers() {
    std::string emptyBoard(constants::EMPTY_FLOOR);
    int currChamber = 0;

    for (int y = 0; y < constants::board::HEIGHT; y++) {
        for (int x = 0; x < constants::board::WIDTH; x++) {
            if (grid[y][x] == '.') {
                bool cells[constants::board::HEIGHT][constants::board::WIDTH] = {};
                expand(emptyBoard, x, y, cells);
                chambers[currChamber] = new Chamber(cells);
                currChamber += 1;
            }
        }
    }
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

void Floor::movePlayer(int px, int py, int nx, int ny) {
    grid[py][px] = underPlayer;
    underPlayer = grid[ny][nx];
    grid[ny][nx] = '@';
}
