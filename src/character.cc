export module character;

import constants;
import floor;
import <string>;

export class Character {
    protected:
    int x, y;
    int hp, maxHp, atk, def;
    Floor& floor;

    public:

    Character(const constants::CharacterInfo& info, Floor& f) : 
        hp{info.hp}, maxHp{info.maxHp}, atk{info.atk}, def{info.def}, floor{f} {}
    virtual ~Character() = default;

    void setPosition(int newX, int newY) { x = newX; y = newY; }
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

    void changeFloor(Floor& newFloor);

    bool isAlive() { return hp > 0; }
    virtual bool isValidMove(const constants::Direction& dir);
};
