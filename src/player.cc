export module player;

import character;
import floor;
import <string>;
import <climits>;

export class Player : public Character {
    public:
    int gold = 0;
    char type;

    Player(int hp, int atk, int def, char t, Floor& f) :
        Character{hp, atk, def, f}, type{t} {}

    virtual void onHit(char enemySymbol) {}
    virtual void onKill(char enemySymbol) {}
    virtual void endTurn() {}
    virtual void applyPotion(int hpMod, int atkMod, int defMod) {
        hp = std::min(maxHp, hp + hpMod);
        atk += atkMod;
        def += defMod;
    }
};

export class Shade : public Player {
    public:
    Shade(Floor& f) : Player{125, 25, 25, 'S', f} {}
};
export class Drow : public Player {
    public:
    Drow(Floor& f) : Player{150, 25, 15, 'D', f} {}
    void applyPotion(int hpMod, int atkMod, int defMod);
};
export class Vampire : public Player {
    public:
    Vampire(Floor& f) : Player{50, 25, 25, 'V', f} { maxHp = INT_MAX; }
    void onHit(char enemySymbol);
};
export class Troll : public Player {
    public:
    Troll(Floor& f) : Player{120, 25, 15, 'T', f} {}
    void endTurn();
};
export class Goblin : public Player {
    public:
    Goblin(Floor& f) : Player{110, 15, 20, 'G', f} {}
    void onKill(char enemySymbol);
};