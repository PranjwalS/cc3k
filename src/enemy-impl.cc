module enemy;

void Enemy::attack(Floor& f, std::string dir) {
    if (!validMove(f, dir)) return;
    auto [atkX, atkY] = toDir(dir) + std::pair<int, int>{x, y};
    if (f.player.x == atkX && f.player.y == atkY) f.player.defend(f, atk);
}
void Enemy::drop(Floor& f) {
    f.player.gold
}
void Enemy::move(Floor& f) {}

void Elf::attack(Floor& f, std::string dir) {}
void Orc::attack(Floor& f, std::string dir) {}
void Halfling::defend(Floor& f, int atkVal) {}
void Dragon::move(Floor& f) {}
void Merchant::attack(Floor& f, std::string dir) {}
void Human::drop(Floor& f) {}