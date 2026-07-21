module player;

import constants;
import floor;
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

bool Player::move(const constants::Direction& dir) {
    if (!isValidMove(dir)) return false;
    auto [dx, dy] = dirToPair(dir);
    x += dx;
    y += dy;
    return true;
}

void Drow::applyPotion(int hpMod, int atkMod, int defMod) {
    double modifier = constants::multiplier::DROW_POTION;
    heal(static_cast<int>(hpMod * modifier));
    atk += static_cast<int>(atkMod * modifier);
    def += static_cast<int>(defMod * modifier);
}

void Vampire::onHit(constants::EnemyRace race) {
    if (race == constants::EnemyRace::Dwarf) takeDamage(constants::VAMPIRE_ALLERGY_HP_LOSS);
    else heal(constants::VAMPIRE_LIFESTEAL);
}

void Troll::endTurn() {
    heal(constants::TROLL_REGEN);
}

void Goblin::onKill(constants::EnemyRace race) {
    gainGold(constants::GOBLIN_STEAL);
}

std::unique_ptr<Player> newPlayer(constants::PlayerRace race, Floor& f) {
    switch (race) {
        case constants::PlayerRace::Shade:
            return std::make_unique<Shade>(f);
        case constants::PlayerRace::Drow:
            return std::make_unique<Drow>(f);
        case constants::PlayerRace::Vampire:
            return std::make_unique<Vampire>(f);
        case constants::PlayerRace::Troll:
            return std::make_unique<Troll>(f);
        case constants::PlayerRace::Goblin:
            return std::make_unique<Goblin>(f);
        default:
            throw std::invalid_argument("Invalid player type");
    }
}
