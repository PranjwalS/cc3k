export module character;

class Floor;

export class Character {
    int x, y;
    int hp, atk, def;
    
    public:
    Floor& attack(Floor& m);
    Floor& defend(Floor& m);
    Floor& step(Floor& m);
    Floor& spawn(Floor& m);
};