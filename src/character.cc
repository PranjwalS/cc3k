export module character;

import floor;
import <string>;

export class Character {
    public:
    int x, y;
    int hp, maxHp, atk, def;

    Character(int hp, int atk, int def, Floor& f) :
        x{0}, y{0}, hp{hp}, maxHp{hp}, atk{atk}, def{def} {
            spawn(f);
        }    
    virtual ~Character() = default;

    bool isAlive() { return hp > 0; }
    void spawn(Floor& f);
    bool validMove(Floor& f, std::string dir);
    void move(Floor& f, std::string dir);
    void takeDamage(int dmg);
};
