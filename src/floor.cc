export module floor;

class Enemy;
class Player;
class Gold;
class Potion;

export class Floor {
    public:
    char grid[30][79];
    Enemy* enemies[30][79];
    Player* player;
    Gold* gold[30][79];
    Potion* potions[30][79];

    Floor();
    bool validSpawn(int x, int y);
};

