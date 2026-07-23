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
    constants::EnemyRace race;
    bool hostile;
    public:

    Enemy(constants::EnemyRace race, Floor& f, bool hostile = true) :
        Character{constants::info(race).value(), f}, race{race}, hostile{hostile} {}

    virtual ~Enemy() = default;

    constants::EnemyRace getRace() const { return race; }
    bool isHostile() const { return hostile; }

    virtual bool evasionChance() { return false; }
    virtual void onDeath(Player& player);
    virtual void move();
    virtual bool isValidMove(const constants::Direction& dir) override;  
};

export class Human : public Enemy {
    public:
    Human(Floor& f) : Enemy{constants::EnemyRace::Human, f} {}
    void onDeath(Player& player);
};

export class Dwarf : public Enemy {
    public:
    Dwarf(Floor& f) : Enemy{constants::EnemyRace::Dwarf, f} {}
};

export class Elf : public Enemy {
    public:
    Elf(Floor& f) : Enemy{constants::EnemyRace::Elf, f} {}
};

export class Orc : public Enemy {
    public:
    Orc(Floor& f) : Enemy{constants::EnemyRace::Orc, f} {}
};

export class Merchant : public Enemy {
    public:
    Merchant(Floor& f) : Enemy{constants::EnemyRace::Merchant, f, false} {}
    void becomeHostile() { hostile = true; }
    void onDeath(Player& player);
};

export class Dragon : public Enemy {
    int hoardX, hoardY;
    public:
    int getHoardX() const { return hoardX; }
    int getHoardY() const { return hoardY; }
    Dragon(Floor& f, int hx, int hy) : 
        Enemy{constants::EnemyRace::Dragon, f}, hoardX{hx}, hoardY{hy} {}
    virtual void move();
    void onDeath(Player& player);
};

export class Halfling : public Enemy {
    public:
    Halfling(Floor& f) : Enemy{constants::EnemyRace::Halfling, f} {}
    bool evasionChance() { return randomChance(constants::probability::HALFLING_EVASION); }
};

export constants::EnemyRace randomEnemy();
export std::unique_ptr<Enemy> newEnemy(constants::EnemyRace race, Floor& floor, 
                                       int dragonHoardX = 0, int dragonHoardY = 0);
