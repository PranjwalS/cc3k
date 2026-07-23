export module chamber;
import <utility>;
import <vector>;
import <optional>;
import <span>;
import <set>;
import constants;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    std::set<std::pair<int, int>> emptyCells;

    public:
    Chamber() = default;
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]);

    const std::set<std::pair<int, int>>& getEmptyCells() const { return emptyCells; };

    void removeEmpty(int x, int y);
    bool contains(int x, int y) const;
    // Returns random empty cell and a direction representing a cell next to the empty cell
    // in the given direction: used for dragon spawning logic
    std::optional<std::pair<std::pair<int, int>, constants::Direction>> randomHoard() const;
    std::optional<std::pair<int, int>> randomEmptyCell() const;
};
