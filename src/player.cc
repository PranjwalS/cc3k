export module player;

import constants;
import character;
import floor;
import <string>;
import <climits>;

export class Player : public Character {
    public:
    int gold = 0;
    constants::race::Player race;

    Player(int hp, int atk, int def, constants::race::Player race, Floor& f) :
        Character{hp, atk, def, f}, race{race} {}

    virtual void onHit(constants::race::Enemy race) {}
    virtual void onKill(constants::race::Enemy race) {}
    virtual void endTurn() {}
    virtual void applyPotion(int hpMod, int atkMod, int defMod) {
        hp = std::min(maxHp, hp + hpMod);
        atk += atkMod;
        def += defMod;
    }
};

export class Shade : public Player {
    public:
    Shade(Floor& f) : Player{125, 25, 25, constants::race::Player::Shade, f} {}
};
export class Drow : public Player {
    public:
    Drow(Floor& f) : Player{150, 25, 15, constants::race::Player::Drow, f} {}
    void applyPotion(int hpMod, int atkMod, int defMod);
};
export class Vampire : public Player {
    public:
    Vampire(Floor& f) : Player{50, 25, 25, constants::race::Player::Vampire, f} {
        maxHp = INT_MAX;
    }
    void onHit(constants::race::Enemy race);
};
export class Troll : public Player {
    public:
    Troll(Floor& f) : Player{120, 25, 15, constants::race::Player::Troll, f} {}
    void endTurn();
};
export class Goblin : public Player {
    public:
    Goblin(Floor& f) : Player{110, 15, 20, constants::race::Player::Goblin, f} {}
    void onKill(constants::race::Enemy race);
};