export module enemy;

import constants;
import character;
import floor;
import random;
import <string>;

export class Enemy : public Character {
    public:
    constants::race::Enemy race;
    bool hostile = false;

    Enemy(int hp, int atk, int def, constants::race::Enemy race, Floor& f) :
        Character{hp, atk, def, f}, race{race} {}

    virtual bool missChance() { return false; }
    virtual void onDeath(int& playerGold) {}
    virtual void move(Floor& f);
};

export class Human : public Enemy {
    public:
    Human(Floor& f) : Enemy{140, 20, 20, constants::race::Enemy::Human, f} {}
    void onDeath(int& playerGold);
};
export class Dwarf : public Enemy {
    public:
    Dwarf(Floor& f) : Enemy{100, 20, 30, constants::race::Enemy::Dwarf, f} {}
};
export class Elf : public Enemy {
    public:
    bool doubleAttack = true;
    Elf(Floor& f) : Enemy{140, 30, 10, constants::race::Enemy::Elf, f} {}
};
export class Orc : public Enemy {
    public:
    Orc(Floor& f) : Enemy{180, 30, 25, constants::race::Enemy::Orc, f} {}
};
export class Merchant : public Enemy {
    public:
    Merchant(Floor& f) : Enemy{30, 70, 5, constants::race::Enemy::Merchant, f} {}
};
export class Dragon : public Enemy {
    public:
    Dragon(Floor& f) : Enemy{150, 20, 20, constants::race::Enemy::Dragon, f} {}
    void move(Floor& f);
};
export class Halfling : public Enemy {
    public:
    Halfling(Floor& f) : Enemy{100, 15, 20, constants::race::Enemy::Halfling, f} {}
    bool missChance() { return random(0, 1) == 0; }
};