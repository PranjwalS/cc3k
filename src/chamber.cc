export module chamber;
import <utility>;
import <vector>;
import constants;

export class Chamber {
    bool occupancy[constants::board::HEIGHT][constants::board::WIDTH];
    public:
    Chamber() = default;
    Chamber(bool (&other)[constants::board::HEIGHT][constants::board::WIDTH]) {
        for (int i = 0; i < constants::board::HEIGHT; i++) {
            for (int j = 0; j < constants::board::WIDTH; j++) {
                occupancy[i][j] = other[i][j];
            }
        }
    };

    bool contains(int x, int y);
};
