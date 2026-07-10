export module player;

import constants;
import character;
import floor;
import <string>;
import <climits>;
import <algorithm>;

export class Player : public Character {
    public:
    int gold = 0;
    constants::Player race;

    Player(int hp, int atk, int def, constants::Player race, Floor& f) :
        Character{hp, atk, def, f}, race{race} {}

    virtual void onHit(constants::Enemy race) {}
    virtual void onKill(constants::Enemy race) {}
    virtual void endTurn() {}
    virtual void applyPotion(int hpMod, int atkMod, int defMod) {
        hp = std::min(maxHp, hp + hpMod);
        hp = std::max(0, hp);
        atk = std::max(0, atk + atkMod);
        def = std::max(0, def + defMod);
    }
};

export class Shade : public Player {
    public:
    Shade(Floor& f) : Player{125, 25, 25, constants::Player::Shade, f} {}
};

export class Drow : public Player {
    public:
    Drow(Floor& f) : Player{150, 25, 15, constants::Player::Drow, f} {}
    void applyPotion(int hpMod, int atkMod, int defMod);
};

export class Vampire : public Player {
    public:
    Vampire(Floor& f) : Player{50, 25, 25, constants::Player::Vampire, f} {
        maxHp = INT_MAX;
    }
    void onHit(constants::Enemy race);
};

export class Troll : public Player {
    public:
    Troll(Floor& f) : Player{120, 25, 15, constants::Player::Troll, f} {}
    void endTurn();
};

export class Goblin : public Player {
    public:
    Goblin(Floor& f) : Player{110, 15, 20, constants::Player::Goblin, f} {}
    void onKill(constants::Enemy race);
};
