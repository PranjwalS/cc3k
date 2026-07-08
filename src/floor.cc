export module floor;

import constants;

using namespace constants;

export class Floor {
    public:
    char grid[board::HEIGHT][board::WIDTH];
    int enemiesIndex[board::HEIGHT][board::WIDTH];
    int goldIndex[board::HEIGHT][board::WIDTH];
    int potionsIndex[board::HEIGHT][board::WIDTH];
    int stairX, stairY;

    Floor();
    bool validSpawn(int x, int y);
    bool isWalkable(int x, int y);
    void addEnemy(int x, int y, int index, constants::Enemy e);
    void removeEnemy(int x, int y);
    void moveEnemy(int px, int py, int nx, int ny); // move from prevx, prevy to newx, newy.
    void addPotion(int x, int y, int index);
    void removePotion(int x, int y);
    void addGold(int x, int y, int index);
    void removeGold(int x, int y);
};
