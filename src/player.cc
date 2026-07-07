export module player;

import <string>;
import <climits>;
import character;
import floor;

export class Player : public Character {
    public:
    int gold = 0;
    Player(int hp, int atk, int def, Floor& f) : Character{hp, atk, def, f} {}
    void attack(Floor& f, std::string dir);
    void defend(Floor& f, int atkVal);
    virtual void endTurn(Floor& f);
};

export class Shade : public Player {
    public:
    Shade(Floor& f) : Player{125, 25, 25, f} {}
};
export class Drow : public Player {
    public:
    Drow(Floor& f) : Player{150, 25, 15, f} {}
};
export class Vampire : public Player {
    public:
    Vampire(Floor& f) : Player{50, 25, 25, f} { maxHp = INT_MAX; }
    void attack(Floor& f, std::string dir);
};

export class Troll : public Player {
    public:
    Troll(Floor& f) : Player{120, 25, 15, f} {}
    void endTurn(Floor& f);  // +5 hp capped at 120
};

export class Goblin : public Player {
    public:
    Goblin(Floor& f) : Player{110, 15, 20, f} {}
    void attack(Floor& f, std::string dir);
};