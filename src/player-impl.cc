module player;

import constants;
import <algorithm>;

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
    hp = std::min(maxHp, hp + (int)(hpMod * 1.5));
    atk += (int)(atkMod * 1.5);
    def += (int)(defMod * 1.5);
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
