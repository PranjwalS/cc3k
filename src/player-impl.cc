module player;

import constants;
import <algorithm>;

void Drow::applyPotion(int hpMod, int atkMod, int defMod) {
    hp = std::min(maxHp, hp + (int)(hpMod * 1.5));
    atk += (int)(atkMod * 1.5);
    def += (int)(defMod * 1.5);
}

void Vampire::onHit(constants::race::Enemy race) {
    if (race == constants::race::Enemy::Dwarf) hp -= 5;
    else hp = std::min(maxHp, hp + 5);
}

void Troll::endTurn() {
    hp = std::min(120, hp + 5);
}

void Goblin::onKill(constants::race::Enemy race) {
    gold += 5;
}