module character;

import constants;
import floor;
import random;
import <algorithm>;

void Character::spawn(Floor& f) {
    x = randomNum(0, constants::board::MAX_Y);
    y = randomNum(0, constants::board::MAX_X);
    while (!f.validSpawn(x, y)) {
        x = randomNum(0, constants::board::MAX_X);
        y = randomNum(0, constants::board::MAX_Y);
    }
}

bool Character::isValidMove(Floor& f, const constants::Direction& dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = x + dx;
    int ty = y + dy;
    if (tx < 0 || tx > constants::board::MAX_X || ty < 0 || ty > constants::board::MAX_Y) return false;
    return f.grid[ty][tx] == '.' || f.grid[ty][tx] == '+' || f.grid[ty][tx] == '#' || 
            f.grid[ty][tx] == 'G' || f.grid[ty][tx] == '\\' ;
}

bool Character::move(Floor& f, const constants::Direction& dir) {
    if (!isValidMove(f, dir)) return false;
    auto [dx, dy] = dirToPair(dir);
    x += dx;
    y += dy;
    return true;
}

void Character::changeHp(int amount) {
    hp = std::min(hp + amount, maxHp);
    hp = std::max(0, hp);
}
void Character::heal(int amount) {
    if (amount <= 0) return;
    changeHp(amount);
}
void Character::takeDamage(int amount) {
    if (amount <= 0) return;
    changeHp(-amount);
}
