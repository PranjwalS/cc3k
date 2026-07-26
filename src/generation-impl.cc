module generation;
import <array>;
import <algorithm>;
import <cstddef>;
import <memory>;
import <optional>;
import <ranges>;
import <string>;
import <vector>;

// ====================================================
// Node
// ====================================================
void Node::getLeaves(std::vector<Node*>& leavesOut) {
    if (isLeaf()) leavesOut.push_back(this);
    else {
        left->getLeaves(leavesOut);
        right->getLeaves(leavesOut);
    }
}

void Node::buildRoom() {
    room.emplace();
    room->addRectangle(std::make_pair(leftX, topY), std::make_pair(rightX, bottomY));
    passages.emplace();
    doors.emplace();
}

void Node::appendRoom(const Node& other) { 
    if (!room || !other.room) return;
    room->addPoints(other.room->getPoints()); 
}

void Node::shrinkRoom(double minScale, double maxScale, int minSize) { 
    if (!room) return;
    room->shrink(minScale, maxScale, minSize);
}

void Node::addPassage(int x1, int x2, int y1, int y2, Node& neighbour) {
    const std::pair<int, int> start{x1, y1};
    const std::pair<int, int> end{x2, y2};
    const auto& points  = room->getPoints();
    const auto& nPoints = neighbour.room->getPoints();

    bool foundStart = false;
    bool foundEnd = false;
    for (const auto& dir : constants::CARDINAL_DIRECTIONS) {
        if (foundStart && foundEnd) break;
        if (!foundStart) {
            auto candidate = start + dir;
            if (std::ranges::find(points, candidate) != points.end()) {
                doors->push_back(candidate);
                foundStart = true;
            }
        }
        if (!foundEnd) {
            auto candidate = end + dir;
            if (std::ranges::find(nPoints, candidate) != points.end()) {
                neighbour.doors->push_back(candidate);
                foundEnd = true;
            }
        }
    }
    passages->addLine(start, end);
}

// ====================================================
// Generation
// ====================================================
std::string Generation::createLayout(int numChambers) {
    binarySpacePartition(numChambers);
    buildDungeon(numChambers);
    // Initialize grid
    std::array<std::array<char, constants::board::WIDTH>, constants::board::HEIGHT> grid;
    for (int y = 0; y < constants::board::HEIGHT; ++y) {
        for (int x = 0; x < constants::board::WIDTH; ++x) {
            if (x == 0 || x == constants::board::MAX_X) {
                grid[y][x] = constants::symbol::VERTICAL_WALL;
            } else if (y == 0 || y == constants::board::MAX_Y) {
                grid[y][x] = constants::symbol::HORIZONTAL_WALL;
            } else {
                grid[y][x] = constants::symbol::EMPTY;
            }
        }
    }
    for (const Shape& chamber : rooms) {
        for (const auto& [x, y] : chamber.getPoints()) {
            // Cannot be external walls
            if (x <= 0 || x >= constants::board::MAX_X || 
                y <= 0 || y >= constants::board::MAX_Y) continue;
            grid[y][x] = constants::symbol::FLOOR;
        }
    }
    for (const Node* leaf : leaves) {
        if (leaf->passages) {
            for (const auto& [x, y] : leaf->passages->getPoints()) {
                if (x <= 0 || x >= constants::board::MAX_X || 
                    y <= 0 || y >= constants::board::MAX_Y) continue;
                grid[y][x] = constants::symbol::PASSAGE;
            }
        }
        if (leaf->doors) {
            for (const auto& [x, y] : *leaf->doors) {
                if (x <= 0 || x >= constants::board::MAX_X || 
                    y <= 0 || y >= constants::board::MAX_Y) continue;
                grid[y][x] = constants::symbol::DOORWAY;
            }
        }
    }

    layout.clear();
    layout.reserve(static_cast<std::size_t>(constants::board::WIDTH) * constants::board::HEIGHT);
    for (int y = 0; y < constants::board::HEIGHT; ++y) {
        layout.append(grid[y].data(), constants::board::WIDTH);
    }
    return layout;
}

bool Generation::divide(Node* node) {
    if (!node->isLeaf()) return false;

    bool canSplitWide = node->width  >= 2 * minLeafSize + 2 * roomPadding;
    bool canSplitTall = node->height >= 2 * minLeafSize + 2 * roomPadding;
    if (!canSplitWide && !canSplitTall) return false;

    bool mustSplit = node->width > maxLeafSize || node->height > maxLeafSize;
    if (!mustSplit && randomChance()) return false;

    bool splitHorizontally;
    if (canSplitWide && canSplitTall) {
        if (node->width > node->height) splitHorizontally = true;
        else if (node->height > node->width) splitHorizontally = false;
        else splitHorizontally = randomChance();
    } else {
        splitHorizontally = canSplitWide;
    }

    if (splitHorizontally) {
        int splitX = node->leftX + roomPadding +
                        randomNum(minLeafSize, node->width - roomPadding - minLeafSize);
        node->left  = std::make_unique<Node>(node->leftX, splitX, node->topY, node->bottomY);
        node->right = std::make_unique<Node>(splitX, node->rightX, node->topY, node->bottomY);
    } else {
        int splitY = node->topY + roomPadding +
                        randomNum(minLeafSize, node->height - roomPadding - minLeafSize);
        node->left  = std::make_unique<Node>(node->leftX, node->rightX, node->topY, splitY);
        node->right = std::make_unique<Node>(node->leftX, node->rightX, splitY, node->bottomY);
    }

    divide(node->left.get());
    divide(node->right.get());
    return true;
}

void Generation::findNeighbours() {
    for (Node* leaf : leaves) {
        for (Node* other : leaves) { 
            if (leaf == other) continue;
            if (leaf->rightX == other->leftX) {
                if (std::max(leaf->topY, other->topY) < std::min(leaf->bottomY, other->bottomY)) {
                    leaf->horNeighbours.push_back(other);
                }
            }
            if (leaf->bottomY == other->topY) {
                if (std::max(leaf->leftX, other->leftX) < std::min(leaf->rightX, other->rightX)) {
                    leaf->vertNeighbours.push_back(other);
                }
            }
        }
    }
}

void Generation::binarySpacePartition(const int numChambers) {
    leaves.clear();
    divide(root.get());
    root->getLeaves(leaves);
    findNeighbours();
}

void Generation::mergeNeighbour(Node& leaf) {
    std::vector<Node*> candidates;
    candidates.reserve(leaf.horNeighbours.size() + leaf.vertNeighbours.size());
    candidates.insert(candidates.end(), leaf.horNeighbours.begin(), leaf.horNeighbours.end());
    candidates.insert(candidates.end(), leaf.vertNeighbours.begin(), leaf.vertNeighbours.end());
    
    if (candidates.empty()) return;

    Node& neighbour = *candidates.at(randomNum(0, static_cast<int>(candidates.size()) - 1));
    leaf.appendRoom(neighbour);

    std::erase(leaf.horNeighbours, &neighbour);
    std::erase(leaf.vertNeighbours, &neighbour);
    
    for (Node* h : neighbour.horNeighbours) {
        if (h == &leaf) continue;
        std::replace(h->horNeighbours.begin(), h->horNeighbours.end(), &neighbour, &leaf);
        std::replace(h->vertNeighbours.begin(), h->vertNeighbours.end(), &neighbour, &leaf);
        if (std::ranges::find(leaf.horNeighbours, h) == leaf.horNeighbours.end()) leaf.horNeighbours.push_back(h);
    }
    for (Node* v : neighbour.vertNeighbours) {
        if (v == &leaf) continue;
        std::replace(v->horNeighbours.begin(), v->horNeighbours.end(), &neighbour, &leaf);
        std::replace(v->vertNeighbours.begin(), v->vertNeighbours.end(), &neighbour, &leaf);
        if (std::ranges::find(leaf.vertNeighbours, v) == leaf.vertNeighbours.end()) leaf.vertNeighbours.push_back(v);
    }
    std::erase(leaves, &neighbour);
}

void Generation::merge(int maxRooms) {
    if (static_cast<int>(leaves.size()) <= maxRooms) return;
    // Guard to prevent infinite loop
    int guard = static_cast<int>(leaves.size()) * 4;
    while (static_cast<int>(leaves.size()) > maxRooms && guard > 0) {
        Node& leaf = *leaves.at(randomNum(0, static_cast<int>(leaves.size()) - 1));
        mergeNeighbour(leaf);
        --guard;
    }
}

void Generation::buildPassages() {
    for (Node* leaf : leaves) {
        for (Node* h : leaf->horNeighbours) {
            int overlapStart = std::max(leaf->topY, h->topY);
            int overlapEnd = std::min(leaf->bottomY, h->bottomY);
            if (overlapEnd - overlapStart > gridSize) {
                int y = randomNum(overlapStart, overlapEnd - gridSize);
                leaf->addPassage(leaf->rightX, y, h->leftX, y + gridSize, *h);
            }
        }
        for (Node* v : leaf->vertNeighbours) {
            int overlapStart = std::max(leaf->leftX, v->leftX);
            int overlapEnd = std::min(leaf->rightX, v->rightX);
            if (overlapEnd - overlapStart > gridSize) {
                int x = randomNum(overlapStart, overlapEnd - gridSize);
                leaf->addPassage(x, leaf->bottomY, x + gridSize, v->topY, *v);
            }
        }
    }
}

void Generation::buildDungeon(int numChambers) {
    rooms.clear();
    for (Node* leaf : leaves) leaf->buildRoom();
    merge(numChambers);
    for (Node* leaf : leaves)  {
        leaf->shrinkRoom(0.4, 0.8, minLeafSize);
        if (leaf->room) rooms.push_back(*leaf->room);
    }
    buildPassages();
}
