export module character;

class Floor;

export class Character {
    int x, y;
    int hp, atk, def;
    
    public:
    Floor& attack(Floor& m, int _x, int _y);
    Floor& defend(Floor& m, Enemy& enemy);
    Floor& move(Floor& m, Direction& dir); 
    bool validMove(Floor& m, Direction& dir); // call validMove first, and it calls move
    Floor& step(Floor& m);
    Floor& spawn(Floor& m, int _x, int _y);
};