export module character;

import <string>;
import floor; // i lwky needed this
import random;
import constants;

class Enemy;

export std::pair<int,int> toDir(std::string dir) {
    if (dir == "no") return {0, -1};
    if (dir == "so") return {0, 1};
    if (dir == "ea") return {1, 0};
    if (dir == "we") return {-1, 0};
    if (dir == "ne") return {1, -1};
    if (dir == "nw") return {-1, -1};
    if (dir == "se") return {1, 1};
    if (dir == "sw") return {-1, 1};
    return {0, 0};
}

export class Character {
    public:
    int x, y;
    int hp, maxHp, atk, def;

    Character(int hp, int atk, int def, Floor& f) :
        x{0}, y{0}, hp{hp}, maxHp{hp}, atk{atk}, def{def} {
            spawn(f);
        }

    virtual void attack(Floor& f, std::string dir) = 0;
    virtual void defend(Floor& f, int atkVal) = 0;
    bool isAlive() { return hp > 0; }
    void spawn(Floor& f);
    bool validMove(Floor& f, std::string dir);
    void move(Floor& f, std::string dir);

    int getX() { return x; }
    int getY() { return y; }
};
