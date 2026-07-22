module character;

import constants;
import floor;
import random;
import <algorithm>;

bool Character::isValidMove(const constants::Direction& dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = x + dx;
    int ty = y + dy;
    if (tx < 0 || tx > constants::board::MAX_X || ty < 0 || ty > constants::board::MAX_Y) return false;
    return floor.getGrid()[ty][tx] == constants::symbol::FLOOR || 
           floor.getGrid()[ty][tx] == constants::symbol::DOORWAY || 
           floor.getGrid()[ty][tx] == constants::symbol::PASSAGE || 
           floor.getGrid()[ty][tx] == constants::symbol::GOLD || 
           floor.getGrid()[ty][tx] == constants::symbol::STAIRS ;
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

void Character::changeFloor(Floor& newFloor) {
    floor = newFloor;
}
