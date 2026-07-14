module enemy;

import floor;
import random;
import constants;
import <vector>;
import <stdexcept>;

void Enemy::onDeath(Player& player) {
    if (randomChance(constants::probability::GOLD_LUCK)) {
        player.gainGold(constants::goldPile::NORMAL);
    } else {
        player.gainGold(constants::goldPile::SMALL);
    }
}

bool Enemy::isValidMove(Floor& f, const constants::Direction& dir) {
    auto [dx, dy] = constants::dirToPair(dir);
    int tx = x + dx;
    int ty = y + dy;
    if (tx < 0 || tx > constants::board::MAX_X || ty < 0 || ty > constants::board::MAX_Y) return false;
    return f.grid[ty][tx] == '.';
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

    auto [dx, dy] = constants::dirToPair(legal[randomNum(0, legal.size() - 1)]);

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

constants::Enemy randomEnemy() {
    using namespace constants::probability::spawn;
    double probabilities[NUM_WEIGHTED_ENEMIES];
    for (int i = 0; i < NUM_WEIGHTED_ENEMIES; ++i) {
        probabilities[i] = ENEMIES[i].probability;
    }
    int idx = randomWeightedIndex(probabilities, NUM_WEIGHTED_ENEMIES);
    return ENEMIES[idx].race;
}

Enemy* newEnemy(constants::Enemy race, Floor& f, int dragonHoardX, int dragonHoardY) {
    switch (race) {
        case constants::Enemy::Human:
            return new Human(f);
        case constants::Enemy::Dwarf:
            return new Dwarf(f);
        case constants::Enemy::Elf:
            return new Elf(f);
        case constants::Enemy::Orc:
            return new Orc(f);
        case constants::Enemy::Merchant:
            return new Merchant(f);
        case constants::Enemy::Dragon:
            return new Dragon(f, dragonHoardX, dragonHoardY);
        case constants::Enemy::Halfling:
            return new Halfling(f);
        default:
            throw std::invalid_argument("Invalid enemy type");
    }
}
