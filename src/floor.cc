export module floor;

import constants;
import gold;
import potion;

export class Floor {
    public:
    char grid[constants::board::HEIGHT][constants::board::WIDTH];
    Gold* gold[constants::board::HEIGHT][constants::board::WIDTH];
    Potion* potions[constants::board::HEIGHT][constants::board::WIDTH];
    int stairX, stairY;

    Floor();
    bool validSpawn(int x, int y);
    bool isWalkable(int x, int y);
};
