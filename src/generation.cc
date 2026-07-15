export module generation;
import shapes;
import <utility>;
import <vector>;
import <stdexcept>;

export class Generation {
    std::vector<Shape> chambers;

    public:
    Generation() {
        ChamberShapeGeneration();
    }
    void ChamberShapeGeneration() {
        Shape chamber1{{3, 3}, {28, 6}};

        Shape chamber2{{39, 3}, {61, 6}};
        chamber2.addRectangle({62, 5}, {69, 6});
        chamber2.addRectangle({70, 6}, {72, 6});
        chamber2.addRectangle({61, 7}, {75, 12});

        Shape chamber3{{38, 10}, {49, 12}};

        Shape chamber4{{4, 15}, {24, 21}};

        Shape chamber5{{65, 16}, {75, 18}};
        chamber5.addRectangle({37, 19}, {75, 21});

        chambers.push_back(chamber1);
        chambers.push_back(chamber2);
        chambers.push_back(chamber3);
        chambers.push_back(chamber4);
        chambers.push_back(chamber5);
    }

    const std::vector<std::pair<int, int>>& getChamberPoints(const int chamberNum) const {
        if (chamberNum < 0 || 
            chamberNum >= static_cast<int>(chambers.size())) {
            throw std::out_of_range("Invalid chamber number");
        }
        return chambers.at(chamberNum).getPoints();
    }
};
