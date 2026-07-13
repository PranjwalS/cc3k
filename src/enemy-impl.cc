module enemy;

import floor;
import random;
import constants;
import <vector>;

void Enemy::onDeath(Player& player) {
    if (randomChance(constants::probability::GOLD_LUCK)) {
        player.gainGold(constants::goldPile::NORMAL);
    } else {
        player.gainGold(constants::goldPile::SMALL);
    }
}

// risk of infinite loop if no valid move exists, deal with later ig
void Enemy::move(Floor& f) {
    std::vector<constants::Direction> legal;
    for (int i = 0; i < constants::NUM_DIRECTIONS; i++) {
        constants::Direction n = static_cast<constants::Direction>(i);
        if (isValidMove(f, n)) {
            legal.push_back(n);
        }
    }

    if (legal.size() == 0) return;

    auto [dx, dy] = constants::dirToPair(legal[randomNum(0, constants::NUM_DIRECTIONS)]);

    f.moveEnemy(x, y, x + dx, y + dy);
    y += dy;
    x += dx;
}

void Dragon::move(Floor& f) {
    // dragon does not move
}

void Human::onDeath(Player& player) {
    player.gainGold(2 * constants::goldPile::NORMAL);
}

void Dwarf::onDeath(Player& player) {
    if (player.getRace() == constants::Player::Vampire) {
        player.loseGold(constants::VAMPIRE_ALLERGY_GOLD_LOSS);
    }
}

void Merchant::onDeath(Player& player) {
    player.gainGold(constants::goldPile::MERCHANT_HOARD);
    becomeHostile();
}
