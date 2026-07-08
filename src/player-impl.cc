module player;

import <algorithm>;

void Drow::applyPotion(int hpMod, int atkMod, int defMod) {
    hp = std::min(maxHp, hp + (int)(hpMod * 1.5));
    atk += (int)(atkMod * 1.5);
    def += (int)(defMod * 1.5);
}

void Vampire::onHit(char enemySymbol) {
    if (enemySymbol == 'W') hp -= 5;
    else hp = std::min(maxHp, hp + 5);
}

void Troll::endTurn() {
    hp = std::min(120, hp + 5);
}

void Goblin::onKill(char enemySymbol) {
    gold += 5;
}