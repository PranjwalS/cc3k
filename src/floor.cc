export module floor;

import constants;
import chamber;
import <vector>;
import <iostream>;

using namespace constants;

export class Floor {
    public:
    int numChambers;
    std::vector<Chamber> chambers;
    char grid[board::HEIGHT][board::WIDTH];
    int enemiesIndex[board::HEIGHT][board::WIDTH];
    int goldIndex[board::HEIGHT][board::WIDTH];
    int potionsIndex[board::HEIGHT][board::WIDTH];
    

    int stairX, stairY;
    char underPlayer = constants::symbol::FLOOR;   // previous char before @ moved on it

    Floor(const int numChambers);
    Floor(Floor&& other);
    Floor& operator=(const Floor& other);

    bool validSpawn(int x, int y);
    bool spawnCapacityReached() const;
    bool isWalkable(int x, int y);

    void initChambers();
    Chamber& chooseChamber();

    void addEnemy(int x, int y, int index, constants::Enemy e);
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
