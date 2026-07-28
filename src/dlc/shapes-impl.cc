module shapes;
import random;
import constants;
import <utility>;
import <vector>;
import <algorithm>;
import <optional>;
import <span>;

Shape::Shape(const std::pair<int, int>& start, const std::pair<int, int>& end) {
    addRectangle(start, end);
}

bool Shape::listHas(const std::vector<std::pair<int,int>>& list,
                    const std::pair<int,int>& point) const {
    return std::find(list.begin(), list.end(), point) != list.end();
}

std::vector<std::pair<int,int>> Shape::getExterior() const {
    std::vector<std::pair<int,int>> exterior;

    for (const auto& p : points) {
        for (auto dir : constants::CARDINAL_DIRECTIONS) {
            if (!listHas(points, p + dir)) {
                exterior.emplace_back(p);
                break;
            }
        }
    }

    return exterior;
}

char Shape::getWallSymbol(const std::pair<int,int>& point) const {
    auto walls = getExterior();

    bool up = listHas(walls, point + constants::Direction::NO);
    bool down = listHas(walls, point + constants::Direction::SO);
    bool left = listHas(walls, point + constants::Direction::WE);
    bool right = listHas(walls, point + constants::Direction::EA);

    if (up || down) return constants::symbol::VERTICAL_WALL;
    if (left || right) return constants::symbol::HORIZONTAL_WALL;

    // Corners are vertical walls by default
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
    int x = start.first;
    int y = start.second;
    points.emplace_back(x, y);
    if (randomChance()) {
        // Horizontal first, vertical after
        while (x != end.first) {
        x += (end.first > x) ? 1 : -1;
        points.emplace_back(x, y);
        }
        while (y != end.second) {
            y += (end.second > y) ? 1 : -1;
            points.emplace_back(x, y);
        }
    } else {
        // Vertical first, horizontal after
        while (y != end.second) {
        y += (end.second > y) ? 1 : -1;
        points.emplace_back(x, y);
        }
        while (x != end.first) {
            x += (end.first > x) ? 1 : -1;
            points.emplace_back(x, y);
        }
    }
    
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

    // Scale dimensions
    double scale = randomNum(minScale, maxScale);
    int newWidth = std::max(static_cast<int>(width * scale), minSize);
    int newHeight = std::max(static_cast<int>(height * scale), minSize);
    
    // Dimensions cannot exceed original dimensions
    newWidth = std::min(newWidth, width);
    newHeight = std::min(newHeight, height);

    while (true) {
        auto mm = getMinMax();
        if (!mm) break;

        int curWidth  = mm->second.first  - mm->first.first  + 1;
        int curHeight = mm->second.second - mm->first.second + 1;
        if (curWidth <= newWidth && curHeight <= newHeight) break;
        if (curWidth <= minSize || curHeight <= minSize) break;
 
        auto boundary = getExterior();
        if (boundary.empty() || boundary.size() >= points.size()) break;
 
        std::erase_if(points, [&](const auto& p) { return listHas(boundary, p); });
    }
}

std::optional<std::pair<int,int>> Shape::pickBound(bool verticalWall, bool maxSide) const {
    auto minMax = getMinMax();
    if (!minMax) return std::nullopt;

    auto [minP, maxP] = *minMax;
    const auto walls = getExterior();
    std::vector<std::pair<int,int>> candidates;

    for (const auto& p : walls) {
        bool onSide = false;

        if (verticalWall) onSide = maxSide ? (p.first == maxP.first) : (p.first == minP.first);
        else onSide = maxSide ? (p.second == maxP.second) : (p.second == minP.second);

        if (!onSide) continue;

        bool hasPrev = false;
        bool hasNext = false;
        for (const auto& q : walls) {
            if (verticalWall) {
                if (q.first == p.first && q.second == p.second - 1) hasPrev = true;
                if (q.first == p.first && q.second == p.second + 1) hasNext = true;
            } else {
                if (q.second == p.second && q.first == p.first - 1) hasPrev = true;
                if (q.second == p.second && q.first == p.first + 1) hasNext = true;
            }
        }
        if (hasPrev && hasNext) candidates.push_back(p);
    }

    if (candidates.empty()) return std::nullopt;

    return candidates.at(randomNum(0, static_cast<int>(candidates.size()) - 1));
}
