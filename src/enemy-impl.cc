module enemy;

import floor;
import random;

void Enemy::move(Floor& f) {
    // random move within chamber
}

void Dragon::move(Floor& f) {}

void Human::onDeath(int& playerGold) {
    playerGold += 4; // 2 normal piles value 2 each??
}