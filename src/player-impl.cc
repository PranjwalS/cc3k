module player;

void Player::attack(Floor& f, std::string dir) {
    if (!validMove(f, dir)) return;
    auto atkDir = toDir(dir);
    int atkX = atkDir.first + x;
    int atkY = atkDir.second + y;
    if (f.enemies[atkX][atkY]) f.enemies[atkX][atkY].defend(f,atk);
}

void Player::defend(Floor& f, int atkVal) {}
void Player::endTurn(Floor& f) {}

void Vampire::attack(Floor& f, std::string dir) {}
void Goblin::attack(Floor& f, std::string dir) {}
void Troll::endTurn(Floor& f) {}
