export module floor;

class Enemy;
class Player;

export class Floor {
    public:
    char grid[30][79];
    Enemy* enemies[30][79];
    Player* player;
    // Potion* potions[30][70];

    Floor();
    bool validSpawn(int x, int y);
};