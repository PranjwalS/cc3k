export module shapes;
import <utility>;
import <vector>;
import <algorithm>;
import <optional>;
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
    
    std::vector<std::pair<int, int>> getExterior() const;
    char getWallSymbol(const std::pair<int, int>& point) const;
    std::vector<std::pair<std::pair<int,int>, char>> getExteriorWalls() const;

    void addPoints(std::span<const std::pair<int, int>> newPoints);
    void addRectangle(const std::pair<int, int>& start, const std::pair<int, int>& end);
    void addLine(const std::pair<int, int>& start, const std::pair<int, int>& end);

    void shrink(double minScale, double maxScale, int minSize);

    private:
    std::optional<std::pair<std::pair<int, int>, std::pair<int, int>>> getMinMax() const;
    bool listHas(const std::vector<std::pair<int,int>>& list,
                        const std::pair<int,int>& point) const;
};
