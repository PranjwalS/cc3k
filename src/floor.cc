export module floor;

import constants;
import chamber;
import <vector>;
import <iostream>;
import <array>;

using namespace constants;

export class Floor {
    int numChambers;
    std::vector<Chamber> chambers;
    std::array<std::array<char, board::WIDTH>, board::HEIGHT> grid;
    std::array<std::array<int, board::WIDTH>, board::HEIGHT> enemiesIndex;
    std::array<std::array<int, board::WIDTH>, board::HEIGHT> goldIndex;
    std::array<std::array<int, board::WIDTH>, board::HEIGHT> potionsIndex;

    int stairX, stairY;
    char underPlayer = constants::symbol::FLOOR;   // previous char before @ moved on it

    void initChambers();
    
    public:

    Floor(const int numChambers);
    Floor(Floor&& other);
    Floor& operator=(const Floor& other);

    int getNumChambers() const { return numChambers; }
    const auto& getChambers() const { return chambers; }
    const auto& getGrid() const { return grid; }
    const auto& getEnemiesIndex() const { return enemiesIndex; }
    const auto& getGoldIndex() const { return goldIndex; }
    const auto& getPotionsIndex() const { return potionsIndex; }
    int getStairX() const { return stairX; }
    int getStairY() const { return stairY; }
    int getUnderPlayer() const { return underPlayer; }

    bool setGrid(int x, int y, char c);

    bool validSpawn(int x, int y) const ;
    bool spawnCapacityReached() const;

    Chamber& chooseChamber();

    void addEnemy(int x, int y, int index, constants::EnemyRace e);
    void removeEnemy(int x, int y);
    void moveEnemy(int px, int py, int nx, int ny); // move from prevx, prevy to newx, newy.

    void addPotion(int x, int y, int index);
    void removePotion(int x, int y);

    void addGold(int x, int y, int index);
    void removeGold(int x, int y);

    void movePlayer(int px, int py, int nx, int ny);
    friend std::ostream& operator<<(std::ostream& os, const Floor& f);
};

export std::ostream& operator<<(std::ostream& os, const Floor& f);
