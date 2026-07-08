module character;

import constants;
import floor;
import random;

void Character::spawn(Floor& f) {
    x = random(0, constants::board::MAX_Y);
    y = random(0, constants::board::MAX_X);
    while (!f.validSpawn(x, y)) {
        x = random(0, constants::board::MAX_Y);
        y = random(0, constants::board::MAX_X);
    }
}

bool Character::validMove(Floor& f, std::string dir) {
    auto [dx, dy] = toDir(dir);
    if (x + dx < 0 || x + dx > constants::board::MAX_X ||
        y + dy < 0 || y + dy > constants::board::MAX_Y) return false;
    return true;
}

void Character::move(Floor& f, std::string dir) {
    if (!validMove(f, dir)) return;
    auto [dx, dy] = toDir(dir);
    x += dx;
    y += dy;
}


void Character::takeDamage(int amount) {
    hp -= amount;
}