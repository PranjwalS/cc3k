export module enemy;

import <string>;
import <utility>;
import geometry;
import character;
import floor;

export class Enemy : public Character {
    public:
    Enemy(int hp, int atk, int def, Floor& f) : Character{hp, atk, def, f} {}
    void attack(Floor& f, std::string dir);
    void defend(Floor& f, int atkVal);
    void drop(Floor& f);
    virtual void move(Floor& f); // not the same as move in Character, this is just for Dragon mainly
};


export class Dwarf : public Enemy {
    public:
    Dwarf(Floor& f) : Enemy{100, 20, 30, f} {}
};
export class Elf : public Enemy {
    public:
    Elf(Floor& f) : Enemy{140, 30, 10, f} {}
    void attack(Floor& f, std::string dir);
};

export class Orc : public Enemy {
    public:
    Orc(Floor& f) : Enemy{180, 30, 25, f} {}
    void attack(Floor& f, std::string dir);
};

export class Halfling : public Enemy {
    public:
    Halfling(Floor& f) : Enemy{100, 15, 20, f} {}
    void defend(Floor& f, int atkVal);
};

export class Dragon : public Enemy {
    public:
    Dragon(Floor& f) : Enemy{150, 20, 20, f} {}
    void move(Floor& f);
};

export class Merchant : public Enemy {
    public:
    bool hostile = false;
    Merchant(Floor& f) : Enemy{30, 70, 5, f} {}
    void attack(Floor& f, std::string dir);
};

export class Human : public Enemy {
    public:
    Human(Floor& f) : Enemy{140, 20, 20, f} {}
    void drop(Floor& f);
};