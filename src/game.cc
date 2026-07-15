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
import <algorithm>;
import <memory>;

export class Game {
    Floor floor;
    std::unique_ptr<Player> player;
    std::vector<Chamber> chambers;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Gold>> gold;
    std::vector<std::unique_ptr<Potion>> potions;
    const int numFloors;
    int floorNum = 1;
    bool merchantsHostile = false;
    bool frozen = false;
    bool forceQuit = false;

    public:

    Game(const constants::Player race,
         const int numFloors = constants::board::NUM_FLOORS, 
         const int numChambers = constants::board::NUM_CHAMBERS):
            floor(numChambers), 
            player{newPlayer(race, floor)}, 
            numFloors{numFloors} {}
    ~Game() = default;

    const Floor& getFloor() const { return floor; }
    const std::unique_ptr<Player>& getPlayer() const { return player; }
    const std::vector<Chamber>& getChambers() const { return chambers; }

    std::vector<const Enemy*> getEnemies() const;
    std::vector<const Gold*> getGold() const;
    std::vector<const Potion*> getPotions() const;
    
    int getFloorNum() const { return floorNum; }
    int getNumFloors() const { return numFloors; }
    
    bool areMerchantsHostile() const { return merchantsHostile; }
    bool isFrozen() const { return frozen; }

    void nextFloor();
    void handleInput(std::string cmd);

    void spawnEnemies();
    void spawnPotions();
    void spawnGold();
    void spawnAll();
    void removeAll();

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
    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

export std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << g.floor;
    return os;
}