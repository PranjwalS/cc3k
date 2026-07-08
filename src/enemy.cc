export module enemy;

import character;
import floor;
import random;
import <string>;

export class Enemy : public Character {
    public:
    char symbol;
    bool hostile = false;

    Enemy(int hp, int atk, int def, char sym, Floor& f) :
        Character{hp, atk, def, f}, symbol{sym} {}

    virtual bool missChance() { return false; }
    virtual void onDeath(int& playerGold) {}
    virtual void move(Floor& f);
};

export class Human : public Enemy {
    public:
    Human(Floor& f) : Enemy{140, 20, 20, 'H', f} {}
    void onDeath(int& playerGold);
};
export class Dwarf : public Enemy {
    public:
    Dwarf(Floor& f) : Enemy{100, 20, 30, 'W', f} {}
};
export class Elf : public Enemy {
    public:
    bool doubleAttack = true;
    Elf(Floor& f) : Enemy{140, 30, 10, 'E', f} {}
};
export class Orc : public Enemy {
    public:
    Orc(Floor& f) : Enemy{180, 30, 25, 'O', f} {}
};
export class Merchant : public Enemy {
    public:
    Merchant(Floor& f) : Enemy{30, 70, 5, 'M', f} {}
};
export class Dragon : public Enemy {
    public:
    Dragon(Floor& f) : Enemy{150, 20, 20, 'D', f} {}
    void move(Floor& f);
};
export class Halfling : public Enemy {
    public:
    Halfling(Floor& f) : Enemy{100, 15, 20, 'L', f} {}
    bool missChance() { return random(0, 1) == 0; }
};