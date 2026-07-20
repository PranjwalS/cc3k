export module enemy;

import constants;
import floor;
import character;
import player;
import random;
import <string>;
import <memory>;

export class Enemy : public Character {
    protected:
    constants::Enemy race;
    bool hostile;
    public:

    Enemy(int hp, int atk, int def, constants::Enemy race, Floor& f, bool hostile = true) :
        Character{hp, atk, def, f}, race{race}, hostile{hostile} {}

    virtual ~Enemy() = default;

    constants::Enemy getRace() const { return race; }
    bool isHostile() const { return hostile; }

    virtual bool evasionChance() { return false; }
    virtual void onDeath(Player& player);
    virtual void move(Floor& f);
    bool isValidMove(Floor& f, const constants::Direction& dir) override;  
};

export class Human : public Enemy {
    public:
    Human(Floor& f) : Enemy{140, 20, 20, constants::Enemy::Human, f} {}
    void onDeath(Player& player);
};

export class Dwarf : public Enemy {
    public:
    Dwarf(Floor& f) : Enemy{100, 20, 30, constants::Enemy::Dwarf, f} {}
};

export class Elf : public Enemy {
    public:
    Elf(Floor& f) : Enemy{140, 30, 10, constants::Enemy::Elf, f} {}
};

export class Orc : public Enemy {
    public:
    Orc(Floor& f) : Enemy{180, 30, 25, constants::Enemy::Orc, f} {}
};

export class Merchant : public Enemy {
    public:
    Merchant(Floor& f) : Enemy{30, 70, 5, constants::Enemy::Merchant, f, false} {}
    void becomeHostile() { hostile = true; }
    void onDeath(Player& player);
};

export class Dragon : public Enemy {
    int hoardX, hoardY;
    public:
    int getHoardX() const { return hoardX; }
    int getHoardY() const { return hoardY; }
    Dragon(Floor& f, int hx, int hy) : Enemy{150, 20, 20, constants::Enemy::Dragon, f}, hoardX{hx}, hoardY{hy} {}
    void move(Floor& f);
    void onDeath(Player& player);
};

export class Halfling : public Enemy {
    public:
    Halfling(Floor& f) : Enemy{100, 15, 20, constants::Enemy::Halfling, f} {}
    bool evasionChance() { return randomChance(constants::probability::HALFLING_EVASION); }
};

export constants::Enemy randomEnemy();
export std::unique_ptr<Enemy> newEnemy(constants::Enemy race, Floor& f, int dragonHoardX = 0, int dragonHoardY = 0);
