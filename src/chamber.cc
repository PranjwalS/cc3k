export module chamber;
import <utility>;
import <vector>;
import <optional>;
import constants;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    std::vector<std::pair<int, int>> occupiedCells;
    std::vector<std::pair<int, int>> emptyCells;

    public:
    Chamber() = default;
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]) {
        for (int i = 0; i < constants::board::HEIGHT; i++) {
            for (int j = 0; j < constants::board::WIDTH; j++) {
                occupancy[i][j] = other[i][j];
                if (occupancy[i][j]) {
                    occupiedCells.emplace_back(j, i);
                } else {
                    emptyCells.emplace_back(j, i);
                }
            }
        }
    };

    const std::vector<std::pair<int, int>>& getOccupiedCells() const { return occupiedCells; };
    const std::vector<std::pair<int, int>>& getEmptyCells() const { return emptyCells; };

    bool contains(int x, int y);

    std::optional<std::pair<int, int>> randomEmptyCell() const;
};
