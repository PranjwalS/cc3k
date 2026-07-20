module enemy;

import floor;
import random;
import constants;
import <vector>;
import <stdexcept>;
import <memory>;
import <array>;

void Enemy::onDeath(Player& player) {
    if (randomChance(constants::probability::GOLD_LUCK)) {
        player.gainGold(constants::goldPile::NORMAL);
    } else {
        player.gainGold(constants::goldPile::SMALL);
    }
}

bool Enemy::isValidMove(Floor& f, const constants::Direction& dir) {
    auto [dx, dy] = dirToPair(dir);
    int tx = x + dx;
    int ty = y + dy;
    if (tx < 0 || tx > constants::board::MAX_X || ty < 0 || ty > constants::board::MAX_Y) return false;
    return f.grid[ty][tx] == constants::symbol::FLOOR;
}

void Enemy::move(Floor& f) {
    std::vector<constants::Direction> legal;
    for (int i = 0; i < constants::NUM_DIRECTIONS; i++) {
        constants::Direction n = static_cast<constants::Direction>(i);
        if (isValidMove(f, n)) {
            legal.push_back(n);
        }
    }

    if (legal.size() == 0) return;

    auto [dx, dy] = dirToPair(legal[randomNum(0, legal.size() - 1)]);

    f.moveEnemy(x, y, x + dx, y + dy);
    y += dy;
    x += dx;
}

void Dragon::move(Floor& f) {
    // dragon does not move
}

void Dragon::onDeath(Player& player) {
    // hoard already placed on floor during spawn, nothing to drop
}

void Human::onDeath(Player& player) {
    player.gainGold(2 * constants::goldPile::NORMAL);
}


void Merchant::onDeath(Player& player) {
    player.gainGold(constants::goldPile::MERCHANT_HOARD);
    becomeHostile();
}

constants::Enemy randomEnemy() {
    using namespace constants::probability::spawn;
    std::array<double, NUM_WEIGHTED_ENEMIES> probabilities;
    for (int i = 0; i < NUM_WEIGHTED_ENEMIES; ++i) {
        probabilities[i] = ENEMIES[i].probability;
    }
    int idx = randomWeightedIndex(probabilities);
    return ENEMIES[idx].race;
}

std::unique_ptr<Enemy> newEnemy(constants::Enemy race, Floor& f, int dragonHoardX, int dragonHoardY) {
    switch (race) {
        case constants::Enemy::Human:
            return std::make_unique<Human>(f);
        case constants::Enemy::Dwarf:
            return std::make_unique<Dwarf>(f);
        case constants::Enemy::Elf:
            return std::make_unique<Elf>(f);
        case constants::Enemy::Orc:
            return std::make_unique<Orc>(f);
        case constants::Enemy::Merchant:
            return std::make_unique<Merchant>(f);
        case constants::Enemy::Dragon:
            return std::make_unique<Dragon>(f, dragonHoardX, dragonHoardY);
        case constants::Enemy::Halfling:
            return std::make_unique<Halfling>(f);
        default:
            throw std::invalid_argument("Invalid enemy type");
    }
}
