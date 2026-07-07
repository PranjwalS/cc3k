module enemy;

import floor;

void Enemy::attack(Floor& f, std::string dir) {}
void Enemy::defend(Floor& f, int atkVal) {}
void Enemy::drop(Floor& f) {}
void Enemy::move(Floor& f) {}

void Elf::attack(Floor& f, std::string dir) {}
void Orc::attack(Floor& f, std::string dir) {}
void Halfling::defend(Floor& f, int atkVal) {}
void Dragon::move(Floor& f) {}
void Merchant::attack(Floor& f, std::string dir) {}
void Human::drop(Floor& f) {}