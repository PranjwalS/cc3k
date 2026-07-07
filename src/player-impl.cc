module player;

void Player::attack(Floor& f, std::string dir) {
    if (!validMove(f, dir)) return;
    auto [atkX, atkY] = toDir(dir) + std::pair<int, int>{x, y};
    if (f.enemies[atkX][atkY]) f.enemies[atkX][atkY].defend(f,atk);
}
void Player::defend(Floor& f, int atkVal) {}
void Player::endTurn(Floor& f) {}

void Vampire::attack(Floor& f, std::string dir) {}
void Goblin::attack(Floor& f, std::string dir) {}
void Troll::endTurn(Floor& f) {}
