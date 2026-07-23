module floor;

import random;
import constants;
import chamber;
import generation;
import <string>;
import <utility>;

Floor::Floor(const int numChambers) : numChambers{numChambers} {
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

Floor::Floor(Floor&& other) {
    std::swap(numChambers, other.numChambers);
    std::swap(chambers, other.chambers);

    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            std::swap(grid[i][j], other.grid[i][j]);
            std::swap(enemiesIndex[i][j], other.enemiesIndex[i][j]);
            std::swap(goldIndex[i][j], other.goldIndex[i][j]);
            std::swap(potionsIndex[i][j], other.potionsIndex[i][j]);
        }
    }
}

Floor& Floor::operator=(const Floor& other) {
    if (this == &other) return *this;

    numChambers = other.numChambers;
    chambers = other.chambers;

    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            grid[i][j] = other.grid[i][j];
            enemiesIndex[i][j] = other.enemiesIndex[i][j];
            goldIndex[i][j] = other.goldIndex[i][j];
            potionsIndex[i][j] = other.potionsIndex[i][j];
        }
    }

    return *this;
}

bool Floor::setGrid(int x, int y, char c) {
    if (!constants::board::isInBounds(x, y)) return false;
    grid[y][x] = c;
    return true;
}

void expand(std::string &emptyBoard, int x, int y,
            bool (&cells)[constants::board::HEIGHT][constants::board::WIDTH]) {
    emptyBoard[y * constants::board::WIDTH + x] = 'x';
    cells[y][x] = true;
    
    auto n = std::pair{x, y} + constants::Direction::NO;
    auto e = std::pair{x, y} + constants::Direction::EA;
    auto s = std::pair{x, y} + constants::Direction::SO;
    auto w = std::pair{x, y} + constants::Direction::WE;
    
    for (auto [nx, ny] : {n, e, s, w}) {
        if (constants::board::isInBounds(nx, ny) && 
            emptyBoard[ny * constants::board::WIDTH + nx] == constants::symbol::FLOOR) {
            expand(emptyBoard, nx, ny, cells);
        }
    }
}

void Floor::initChambers() {
    std::string emptyBoard(constants::EMPTY_FLOOR);
    for (int y = 0; y < constants::board::HEIGHT; y++) {
        for (int x = 0; x < constants::board::WIDTH; x++) {
            if (emptyBoard[y * constants::board::WIDTH + x] == constants::symbol::FLOOR) {
                bool cells[constants::board::HEIGHT][constants::board::WIDTH] = {};
                expand(emptyBoard, x, y, cells);
                chambers.emplace_back(cells);
            }
        }
    }
}

Chamber& Floor::chooseChamber() { 
    return chambers.at(randomNum(0, numChambers - 1));
}

bool Floor::validSpawn(int x, int y) const {
    return grid[y][x] == constants::symbol::FLOOR && 
                         goldIndex[y][x] == -1 && 
                         potionsIndex[y][x] == -1;
}

bool Floor::spawnCapacityReached() const {
    for (const Chamber& c : chambers) {
        if (!c.getEmptyCells().empty()) return false;
    }
    return true;
}

void Floor::addEnemy(int x, int y, int index, constants::EnemyRace race) {
    enemiesIndex[y][x] = index;
    grid[y][x] = enemyRaceToSymbol(race);
}

void Floor::removeEnemy(int x, int y) {
    enemiesIndex[y][x] = -1;
    grid[y][x] = constants::symbol::FLOOR;
}

void Floor::moveEnemy(int px, int py, int nx, int ny) {
    enemiesIndex[ny][nx] = enemiesIndex[py][px];
    grid[ny][nx] = grid[py][px];
    removeEnemy(px, py);
}

void Floor::addPotion(int x, int y, int index) {
    potionsIndex[y][x] = index;
    grid[y][x] = constants::symbol::POTION;
}

void Floor::removePotion(int x, int y) {
    potionsIndex[y][x] = -1;
    grid[y][x] = constants::symbol::FLOOR;
}

void Floor::addGold(int x, int y, int index) {
    goldIndex[y][x] = index;
    grid[y][x] = constants::symbol::GOLD;
}

void Floor::removeGold(int x, int y) {
    goldIndex[y][x] = -1;
    grid[y][x] = constants::symbol::FLOOR;
}

void Floor::movePlayer(int px, int py, int nx, int ny) {
    grid[py][px] = underPlayer;
    underPlayer = grid[ny][nx];
    grid[ny][nx] = constants::symbol::PLAYER;
}

std::ostream& operator<<(std::ostream& os, const Floor& f) {
    for (int i = 0; i < constants::board::HEIGHT; i++) {
        for (int j = 0; j < constants::board::WIDTH; j++) {
            // Reset after colour change not necessary; just for safety
            os << symbolToColour(f.grid[i][j]) << f.grid[i][j] << constants::colour::RESET;
        }
        os << "\n";
    }

    return os;
}
