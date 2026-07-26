module generation;
import shapes;
import random;
import constants;
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

void Node::addPassage(int x1, int y1, int x2, int y2, Node& neighbour) {
    const std::pair<int, int> startDoor{x1, y1};
    const std::pair<int, int> endDoor{x2, y2};
    
    doors->push_back(startDoor);
    neighbour.doors->push_back(endDoor);

    passages->addLine(startDoor, endDoor);
}

// ====================================================
// Generation
// ====================================================

Generation::Generation(int minLeafSize, int maxLeafSize) : 
        minLeafSize{minLeafSize}, maxLeafSize{maxLeafSize} {
    root = std::make_unique<Node>(2, constants::board::WIDTH - 2, 2, constants::board::HEIGHT - 2);
    createLayout(constants::board::NUM_CHAMBERS);
}

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
        if (!leaf->room) continue;
        for (const auto& wall : leaf->room->getExterior()) {
            auto [x, y] = wall;
            if (x <= 0 || x >= constants::board::MAX_X || 
                y <= 0 || y >= constants::board::MAX_Y) continue;
            grid[y][x] = leaf->room->getWallSymbol(wall);
        }
    }
    for (const Node* leaf : leaves) {
        if (!leaf->passages) continue;
        for (const auto& [x, y] : leaf->passages->getPoints()) {
            if (x <= 0 || x >= constants::board::MAX_X || 
                y <= 0 || y >= constants::board::MAX_Y) continue;
            grid[y][x] = constants::symbol::PASSAGE;
        }
    }
    for (const Node* leaf : leaves) {
        if (!leaf->doors) continue;
        for (const auto& [x, y] : *leaf->doors) {
            if (x <= 0 || x >= constants::board::MAX_X || 
                y <= 0 || y >= constants::board::MAX_Y) continue;
            grid[y][x] = constants::symbol::DOORWAY;
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
    int guard = static_cast<int>(leaves.size()) * constants::generation::GUARD_NUM;
    while (static_cast<int>(leaves.size()) > maxRooms && guard > 0) {
        Node& leaf = *leaves.at(randomNum(0, static_cast<int>(leaves.size()) - 1));
        mergeNeighbour(leaf);
        --guard;
    }
}

void Generation::buildPassages() {
    for (Node* leaf : leaves) {
        auto minMaxA = leaf->room->getMinMax();
        if (!minMaxA) continue;
        auto [minA, maxA] = *minMaxA;
        const auto wallsA = leaf->room->getExterior();

        for (Node* h : leaf->horNeighbours) {
            auto minMaxB = h->room->getMinMax();
            if (!minMaxB) continue;
            auto [minB, maxB] = *minMaxB;
            const auto wallsB = h->room->getExterior();

            std::vector<int> commonYs;
            for (const auto& a : wallsA) {
                if (a.first != maxA.first) continue;
                for (const auto& b : wallsB) {
                    if (b.first == minB.first && a.second == b.second) {
                        commonYs.push_back(a.second);
                    }
                }
            }

            if (commonYs.empty()) continue;

            int y = commonYs.at(randomNum(0, static_cast<int>(commonYs.size()) - 1));
            leaf->addPassage(maxA.first, y, minB.first, y, *h);
        }

        for (Node* v : leaf->vertNeighbours) {
            auto minMaxB = v->room->getMinMax();
            if (!minMaxB) continue;
            auto [minB, maxB] = *minMaxB;
            const auto wallsB = v->room->getExterior();

            std::vector<int> commonXs;
            for (const auto& a : wallsA) {
                if (a.second != maxA.second) continue;
                for (const auto& b : wallsB) {
                    if (b.second == minB.second && a.first == b.first) {
                        commonXs.push_back(a.first);
                    }
                }
            }

            if (commonXs.empty()) continue;

            int x = commonXs.at(randomNum(0, static_cast<int>(commonXs.size()) - 1));
            leaf->addPassage(x, maxA.second, x, minB.second, *v);
        }
    }
}

void Generation::buildDungeon(int numChambers) {
    rooms.clear();
    for (Node* leaf : leaves) leaf->buildRoom();
    merge(numChambers);
    for (Node* leaf : leaves)  {
        leaf->shrinkRoom(constants::generation::MIN_SCALE, 
                         constants::generation::MAX_SCALE, 
                         minLeafSize);
        if (leaf->room) rooms.push_back(*leaf->room);
    }
    buildPassages();
}
