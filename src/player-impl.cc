module player;

import floor;

void Player::attack(Floor& f, std::string dir) {}
void Player::defend(Floor& f, int atkVal) {}
void Player::endTurn(Floor& f) {}

void Vampire::attack(Floor& f, std::string dir) {}
void Goblin::attack(Floor& f, std::string dir) {}
void Troll::endTurn(Floor& f) {}