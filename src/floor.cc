export module floor;

import constants;
import gold;
import potion;

using namespace constants;

export class Floor {
    public:
    char grid[board::HEIGHT][board::WIDTH];
    Gold* gold[board::HEIGHT][board::WIDTH];
    Potion* potions[board::HEIGHT][board::WIDTH];
    int stairX, stairY;

    Floor();
    bool validSpawn(int x, int y);
    bool isWalkable(int x, int y);
};
