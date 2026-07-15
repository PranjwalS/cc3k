export module chamber;
import <utility>;
import <vector>;
import <optional>;
import <span>;
import constants;
import generation;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    std::vector<std::pair<int, int>> occupiedCells;
    std::vector<std::pair<int, int>> emptyCells;

    public:
    Chamber() { refreshEmptyCells(); }
    Chamber(const int chamberNum, const Generation& generation);
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]);

    const std::vector<std::pair<int, int>>& getOccupiedCells() const { return occupiedCells; };
    const std::vector<std::pair<int, int>>& getEmptyCells() const { return emptyCells; };

    void refreshEmptyCells();

    void addSpawnableCells(std::span<const std::pair<int, int>> cells);

    bool contains(int x, int y) const;

    std::optional<std::pair<int, int>> randomEmptyCell() const;
};
