export module floor;

import constants;

class Enemy;
class Player;
class Gold;
class Potion;

export class Floor {
    public:
    char grid[BOARD_WIDTH][BOARD_HEIGHT];
    Enemy* enemies[BOARD_WIDTH][BOARD_HEIGHT];
    Player* player;
    Gold* gold[BOARD_WIDTH][BOARD_HEIGHT];
    Potion* potions[BOARD_WIDTH][BOARD_HEIGHT];

    Floor();
    bool validSpawn(int x, int y);
};
