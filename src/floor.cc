export module floor;

import constants;

class Enemy;
class Player;
class Gold;
class Potion;

export class Floor {
    public:
    char grid[constants::board::WIDTH][constants::board::HEIGHT];
    Enemy* enemies[constants::board::WIDTH][constants::board::HEIGHT];
    Player* player;
    Gold* gold[constants::board::WIDTH][constants::board::HEIGHT];
    Potion* potions[constants::board::WIDTH][constants::board::HEIGHT];

    Floor();
    bool validSpawn(int x, int y);
};
