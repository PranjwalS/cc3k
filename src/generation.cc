export module generation;
import shapes;
import <utility>;
import <vector>;
import <stdexcept>;

export class Generation {
    int width;
    int height;
    int numChambers;
    std::vector<Shape> chambers;

    public:
    Generation(const int width, const int height, const int numChambers) : 
        width{width}, height{height}, numChambers{numChambers}, chambers(numChambers) {
        ChamberShapeGeneration();
    }

    void binarySpacePartition(const int numChambers) {}

    void ChamberShapeGeneration() {
        binarySpacePartition(numChambers);
    }

    const std::vector<std::pair<int, int>>& getChamberPoints(const int chamberNum) const {
        if (chamberNum < 0 || 
            chamberNum >= static_cast<int>(chambers.size())) {
            throw std::out_of_range("Invalid chamber number");
        }
        return chambers.at(chamberNum).getPoints();
    }
};
