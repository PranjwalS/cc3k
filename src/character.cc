export module character;

import constants;
import floor;
import <string>;

export class Character {
    protected:
    int x, y;
    int hp, maxHp, atk, def;

    public:

    Character(int hp, int atk, int def, Floor& f) :
        x{0}, y{0}, hp{hp}, maxHp{hp}, atk{atk}, def{def} {
            spawn(f);
        }    
    virtual ~Character() = default;

    int getX() const { return x; }
    int getY() const { return y; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAtk() const { return atk; }
    int getDef() const { return def; }

    void changeHp(int amount);
    // heal and takeDamage must take in positive integers
    void heal(int amount);
    void takeDamage(int amount);

    bool isAlive() { return hp > 0; }
    void spawn(Floor& f);
    virtual bool isValidMove(Floor& f, const constants::Direction& dir);
    bool move(Floor& f, const constants::Direction& dir);
};
