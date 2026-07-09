module character;

import constants;
import floor;
import random;

void Character::spawn(Floor& f) {
    x = randomNum(0, constants::board::MAX_Y);
    y = randomNum(0, constants::board::MAX_X);
    while (!f.validSpawn(x, y)) {
        x = randomNum(0, constants::board::MAX_Y);
        y = randomNum(0, constants::board::MAX_X);
    }
}

// only checks if move is in the confines of Floor.
bool Character::isValidMove(Floor& f, const constants::Direction& dir) {
    auto [dx, dy] = constants::dirToPair(dir);
    int tx = x + dx;
    int ty = y + dy;
    return tx >= 0 && tx <= constants::board::MAX_X && ty >= 0 && ty <= constants::board::MAX_Y;
}

void Character::move(Floor& f, const constants::Direction& dir) {
    if (!isValidMove(f, dir)) return;
    auto [dx, dy] = constants::dirToPair(dir);
    x += dx;
    y += dy;
}


void Character::takeDamage(int amount) {
    hp -= amount;
}
