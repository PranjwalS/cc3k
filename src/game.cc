export module game;

import constants;
import character;
import player;
import enemy;
import floor;
import potion;
import gold;
import <string>;
import <vector>;
import <cmath>;
import <algorithm>;

export class Game {
    public:
    Floor floor;
    Player* player = nullptr;
    std::vector<Enemy*> enemies;
    std::vector<Gold*> gold;
    std::vector<Potion*> potions;
    int floorNum = 1;
    bool merchantsHostile = false;
    bool frozen = false;

    Game();
    ~Game();

    void init(constants::Player race);
    void nextFloor();
    void handleInput(std::string cmd);

    void spawnEnemies();
    void spawnPotions();
    void spawnGold();

    bool playerMove(constants::Direction dir);
    bool playerAttack(constants::Direction dir);
    void usePotion(constants::Direction dir);
    void enemyTurns();

    int calcDamage(int atkVal, int defVal);

    bool isOver();
    int score();
    void display();
};
