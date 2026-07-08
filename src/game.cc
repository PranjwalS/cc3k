export module game;

import character;
import player;
import enemy;
import floor;
import potion;
import gold;
import random;
import <string>;
import <vector>;
import <cmath>;
import <algorithm>;

export class Game {
    public:
    Floor floor;
    Player* player = nullptr;
    std::vector<Enemy*> enemies;
    int floorNum = 1;
    bool merchantsHostile = false;
    bool frozen = false;

    Game() {}
    ~Game() { delete player; for (auto e : enemies) delete e; }

    void init(char race);
    void nextFloor();
    void handleInput(std::string cmd);

    void spawnEnemies();
    void spawnPotions();
    void spawnGold();

    void playerMove(std::string dir);
    void playerAttack(std::string dir);
    void usePotion(std::string dir);
    void enemyTurns();

    int calcDamage(int atkVal, int defVal) {
        return (int)std::ceil((100.0 / (100.0 + defVal)) * atkVal);
    }

    bool isOver() { return !player->isAlive() || floorNum > 5; }
    int score();
    void display();
};