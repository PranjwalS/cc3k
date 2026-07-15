export module shapes;
import <utility>;
import <vector>;
import <span>;

export class Shape {
    std::vector<std::pair<int, int>> points;
    
    public:
    Shape() = default;

    // Rectangle constructor
    Shape(const std::pair<int, int>& start, const std::pair<int, int>& end);

    // Points array/vector constructor
    Shape(std::span<const std::pair<int, int>> newPoints);

    const std::vector<std::pair<int, int>>& getPoints() const { return points; };

    void addPoints(std::span<const std::pair<int, int>> newPoints);
    void addRectangle(const std::pair<int, int>& start, const std::pair<int, int>& end);
};
