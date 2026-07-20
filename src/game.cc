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
import <set>;

export class Game {
    Floor floor;
    std::unique_ptr<Player> player;
    std::vector<Chamber> chambers;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Gold>> gold;
    std::vector<std::unique_ptr<Potion>> potions;
    std::set<constants::PotionType> knownPotions;
    const int numFloors;
    int floorNum = 1;
    bool merchantsHostile = false;
    bool frozen = false;
    bool forceQuit = false;
    int tempAtk = 0;
    int tempDef = 0;

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
    
    std::string currentAction = "";
    
    void setAction(const std::string& action) { currentAction = action; }
    void appendAction(const std::string& action) { currentAction += action; }

    int getFloorNum() const { return floorNum; }
    int getNumFloors() const { return numFloors; }
    
    bool areMerchantsHostile() const { return merchantsHostile; }
    bool isFrozen() const { return frozen; }

    void nextFloor();

    Chamber& spawnPlayer();
    void spawnStairs(Chamber& playerChamber);
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
    
    void displayAction(std::ostream& os) const;
    void displayInfo(std::ostream& os) const;
    void displayScore(std::ostream& os) const;
    void display(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

export std::ostream& operator<<(std::ostream& os, const Game& g) {
    g.display(os);
    return os;
}