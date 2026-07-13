module enemy;

import floor;
import random;
import constants;

void Enemy::onDeath(Player& player) {
    if (randomChance(constants::probability::GOLD_LUCK)) {
        player.gainGold(constants::goldPile::NORMAL);
    } else {
        player.gainGold(constants::goldPile::SMALL);
    }
}

// risk of infinite loop if no valid move exists, deal with later ig
void Enemy::move(Floor& f) {
    while (true) {
        constants::Direction n = static_cast<constants::Direction>(randomNum(0, constants::NUM_DIRECTIONS - 1));
        auto [dx, dy] = constants::dirToPair(n);
        if (isValidMove(f, n) && f.grid[y + dy][x + dx] == '.') {
            f.moveEnemy(x, y, x+dx, y+dy);
            y += dy;
            x += dx;
            break;
        }
    }
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
