export module chamber;
import <utility>;
import <vector>;
import constants;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    std::vector<std::pair<int, int>> occupied;
    std::vector<std::pair<int, int>> empty;

    public:
    Chamber() = default;
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]) {
        for (int i = 0; i < constants::board::HEIGHT; i++) {
            for (int j = 0; j < constants::board::WIDTH; j++) {
                occupancy[i][j] = other[i][j];
                if (occupancy[i][j]) {
                    occupied.emplace_back(j, i);
                } else {
                    empty.emplace_back(j, i);
                }
            }
        }
    };

    const std::vector<std::pair<int, int>>& getOccupiedCells() const { return occupied; };
    const std::vector<std::pair<int, int>>& getEmptyCells() const { return empty; };

    bool contains(int x, int y);
};
