export module chamber;
import <utility>;
import <vector>;
import <optional>;
import <span>;
import <set>;
import constants;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    std::vector<std::pair<int, int>> occupiedCells;
    std::set<std::pair<int, int>> emptyCells;

    public:
    Chamber() = default;
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]);

    const std::vector<std::pair<int, int>>& getOccupiedCells() const { return occupiedCells; };
    const std::set<std::pair<int, int>>& getEmptyCells() const { return emptyCells; };

    // void refreshEmptyCells();
    // void addSpawnableCells(std::span<const std::pair<int, int>> cells);
    void removeEmpty(int x, int y);
    bool contains(int x, int y) const;
    std::optional<std::pair<std::pair<int, int>, constants::Direction>> randomHoard() const; // for dragon
    std::optional<std::pair<int, int>> randomEmptyCell() const;
};
