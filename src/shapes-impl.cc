module shapes;
import random;
import constants;
import <utility>;
import <vector>;
import <optional>;
import <span>;
import <unordered_set>;

Shape::Shape(const std::pair<int, int>& start, const std::pair<int, int>& end) {
    addRectangle(start, end);
}

struct PairHash {
    std::size_t operator()(const std::pair<int,int>& p) const noexcept {
        return std::hash<int>{}(p.first) ^
               (std::hash<int>{}(p.second) << 1);
    }
};

std::vector<std::pair<int,int>> Shape::getExterior() const {
    std::vector<std::pair<int,int>> exterior;

    std::unordered_set<std::pair<int,int>, PairHash> pointSet(
        points.begin(), points.end()
    );

    for (const auto& [x, y] : points) {
        bool exposed =
            !pointSet.contains({x - 1, y}) ||
            !pointSet.contains({x + 1, y}) ||
            !pointSet.contains({x, y - 1}) ||
            !pointSet.contains({x, y + 1});

        if (exposed)
            exterior.emplace_back(x, y);
    }

    return exterior;
}

char Shape::getWallSymbol(const std::pair<int,int>& point) const {
    auto exterior = getExterior();

    std::unordered_set<std::pair<int,int>, PairHash> exteriorSet(
        exterior.begin(), exterior.end()
    );

    int x = point.first;
    int y = point.second;

    bool up = exteriorSet.contains({x, y - 1});
    bool down = exteriorSet.contains({x, y + 1});
    bool left = exteriorSet.contains({x - 1, y});
    bool right = exteriorSet.contains({x + 1, y});

    if (up || down) return constants::symbol::VERTICAL_WALL;
    if (left || right) return constants::symbol::HORIZONTAL_WALL;
    // Corner case
    return constants::symbol::VERTICAL_WALL;
}

Shape::Shape(std::span<const std::pair<int, int>> newPoints) : 
    points(newPoints.begin(), newPoints.end()) {}

void Shape::addPoints(std::span<const std::pair<int, int>> newPoints) {
    points.insert(points.end(), newPoints.begin(), newPoints.end());
}

void Shape::addRectangle(const std::pair<int, int>& start, 
                         const std::pair<int, int>& end) {
    for (int y = start.second; y < end.second; ++y) {
        for (int x = start.first; x < end.first; ++x) {
            points.emplace_back(x, y);
        }
    }
}

void Shape::addLine(const std::pair<int, int>& start, const std::pair<int, int>& end) {
    addRectangle(start, end);
}

std::optional<std::pair<std::pair<int, int>, std::pair<int, int>>> Shape::getMinMax() const {
    if (points.empty()) return std::nullopt;

    int minX = points[0].first;
    int maxX = points[0].first;
    int minY = points[0].second;
    int maxY = points[0].second;

    for (const auto& [x, y] : points) {
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }

    return std::make_pair(std::make_pair(minX, minY), std::make_pair(maxX, maxY));
}

void Shape::shrink(double minScale, double maxScale, int minSize) {
    if (points.empty()) return;

    // Find minimum and maximum x and y values
    auto minMax = getMinMax();
    if (!minMax) return;

    int minX = minMax->first.first;
    int minY = minMax->first.second;
    int maxX = minMax->second.first;
    int maxY = minMax->second.second;

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    // Width and height are scaled separately
    double widthScale = randomNum(minScale, maxScale);
    double heightScale = randomNum(minScale, maxScale);

    // Scale dimensions
    int newWidth = std::max(static_cast<int>(width * widthScale), minSize);
    int newHeight = std::max(static_cast<int>(height * heightScale), minSize);
    
    // Dimensions cannot exceed original dimensions
    newWidth = std::min(newWidth, width);
    newHeight = std::min(newHeight, height);

    // Center shape
    int centerX = (minX + maxX) / 2;
    int centerY = (minY + maxY) / 2;

    int newMinX = centerX - newWidth / 2;
    int newMaxX = newMinX + newWidth - 1;
    int newMinY = centerY - newHeight / 2;
    int newMaxY = newMinY + newHeight - 1;

    for (auto point = points.begin(); point != points.end(); ) {
        auto [x, y] = *point;
        if (x < newMinX || x > newMaxX || y < newMinY || y > newMaxY) {
            point = points.erase(point);
        } else ++point;
    }
}
