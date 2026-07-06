export module floor;

import <vector>;
class Enemy;
class Player;

export class Floor {
    Enemy* enemies[30][79];
    // Potion* potions[30][70];
    Player* player;

    public:
    Floor();
};