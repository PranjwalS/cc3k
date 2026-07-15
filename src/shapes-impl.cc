module shapes;
import <utility>;
import <vector>;
import <span>;

Shape::Shape(const std::pair<int, int>& start, const std::pair<int, int>& end) {
    addRectangle(start, end);
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
