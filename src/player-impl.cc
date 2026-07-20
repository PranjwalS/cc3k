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

void Vampire::onHit(constants::EnemyRace race) {
    if (race == constants::EnemyRace::Dwarf) hp -= 5;
    else hp = std::min(maxHp, hp + 5);
}

void Troll::endTurn() {
    hp = std::min(120, hp + 5);
}

void Goblin::onKill(constants::EnemyRace race) {
    gold += 5;
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
