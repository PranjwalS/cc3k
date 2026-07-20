module player;

import constants;
import floor;
import <algorithm>;
import <stdexcept>;
import <memory>;

void Player::changeGold(int amount) {
    gold += amount;
    if (amount > 0) score += amount;
}
void Player::gainGold(int amount) {
    if (amount <= 0) return;
    changeGold(amount);
}
void Player::loseGold(int amount) {
    if (amount <= 0) return;
    changeGold(-amount);
}


void Drow::applyPotion(int hpMod, int atkMod, int defMod) {
    double modifier = constants::multiplier::DROW_POTION;
    hp = std::min(maxHp, hp + (int)(hpMod * modifier));
    atk += (int)(atkMod * modifier);
    def += (int)(defMod * modifier);
}

void Vampire::onHit(constants::Enemy race) {
    if (race == constants::Enemy::Dwarf) hp -= 5;
    else hp = std::min(maxHp, hp + 5);
}

void Troll::endTurn() {
    hp = std::min(120, hp + 5);
}

void Goblin::onKill(constants::Enemy race) {
    gold += 5;
}

std::unique_ptr<Player> newPlayer(constants::Player race, Floor& f) {
    switch (race) {
        case constants::Player::Shade:
            return std::make_unique<Shade>(f);
        case constants::Player::Drow:
            return std::make_unique<Drow>(f);
        case constants::Player::Vampire:
            return std::make_unique<Vampire>(f);
        case constants::Player::Troll:
            return std::make_unique<Troll>(f);
        case constants::Player::Goblin:
            return std::make_unique<Goblin>(f);
        default:
            throw std::invalid_argument("Invalid player type");
    }
}
