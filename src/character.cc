export module character;

import direction;
class Enemy;
class Floor;

export class Character {
    protected:
    int x, y;
    int hp, atk, def;

    Character(int hp, int atk, int def, Floor& m) : 
        hp{hp}, atk{atk}, def{def} {
            // spawn(m);
        }

    public:
    Floor& attack(Floor& m, int _x, int _y);
    Floor& defend(Floor& m, Enemy& enemy);
    Floor& move(Floor& m, Direction& dir); 
    bool validMove(Floor& m, Direction& dir); // call validMove first, and it calls move
    Floor& step(Floor& m);
    Floor& spawn(Floor& m, int _x, int _y);
};