export module game;

import random;
import constants;
import character;
import player;
import enemy;
import floor;
import potion;
import gold;
import chamber;
import <string>;
import <vector>;
import <cmath>;
import <algorithm>;

export class Game {
    Floor floor;
    Player* player;
    const int numChambers;
    std::vector<Chamber> chambers;
    std::vector<Enemy*> enemies;
    std::vector<Gold*> gold;
    std::vector<Potion*> potions;
    const int numFloors;
    int floorNum = 1;
    bool merchantsHostile = false;
    bool frozen = false;
    bool forceQuit = false;

    public:

    Game(Player* player = nullptr, 
        const int numFloors = constants::board::NUM_FLOORS, 
        const int numChambers = constants::board::NUM_CHAMBERS);
    ~Game();

    const Floor& getFloor() const { return floor; }
    const Player* const getPlayer() const { return player; }
    const std::vector<Chamber>& getChambers() const { return chambers; }

    const std::vector<const Enemy*> getEnemies() const;
    const std::vector<const Gold*> getGold() const;
    const std::vector<const Potion*> getPotions() const;
    
    int getFloorNum() const { return floorNum; }
    int getNumFloors() const { return numFloors; }
    int getNumChambers() const { return numChambers; }
    
    bool areMerchantsHostile() const { return merchantsHostile; }
    bool isFrozen() const { return frozen; }

    void init(constants::Player race);
    void nextFloor();
    void handleInput(std::string cmd);

    int chooseChamber() const { return randomNum(0, numChambers); }
    void spawnEnemies();
    void spawnPotions();
    void spawnGold();

    bool playerMove(constants::Direction dir);
    bool playerAttack(constants::Direction dir);
    void usePotion(constants::Direction dir);
    void enemyTurns();
    void enemyAttack(Enemy& e);

    int calcDamage(int atkVal, int defVal) const;

    void quitGame();
    bool isOver() const;
    bool isWon() const;
    void displayScore() const;

    void display() const;
};
