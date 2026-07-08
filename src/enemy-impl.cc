module enemy;

import floor;
import random;
import constants;

void Enemy::move(Floor& f) {
    while (true) {
        constants::Direction n = static_cast<constants::Direction>(random(0, constants::NUM_DIRECTIONS - 1));
        auto [dx, dy] = constants::dirToPair(n);
        if (constants::isValidMove(x, y, n) && f.grid[y + dy][x + dx] == '.') {
            y += dy;
            x += dx;
            break;
        }
    }
}

void Dragon::move(Floor& f) {
    // dragon does not move
}

void Human::onDeath(int& playerGold) {
    playerGold += 4;
}
