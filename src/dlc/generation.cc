export module generation;
import shapes;
import random;
import constants;
import <utility>;
import <vector>;
import <optional>;
import <memory>;
import <string>;

// Binary Space Partitioning node
// Note: Leaves represent possible dungeon chambers
struct Node {
    int leftX, rightX;
    int topY, bottomY;
    
    int width, height;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    
    std::vector<Node*> horNeighbours;
    std::vector<Node*> vertNeighbours;

    std::optional<Shape> room;
    std::optional<Shape> passages;
    std::optional<std::vector<std::pair<int, int>>> doors;

    Node(int lx, int rx, int ty, int by) : 
        leftX{lx}, rightX{rx}, topY{ty}, bottomY{by},
        width{rightX - leftX}, height{bottomY - topY} {}

    bool isLeaf() const { return !left && !right; }
    void getLeaves(std::vector<Node*>& leavesOut);

    void buildRoom();
    void appendRoom(const Node& other);
    void shrinkRoom(double minScale, double maxScale, int minSize);

    void addPassage(int x1, int y1, int x2, int y2, Node& neighbour);
};

// Use binary space partitioning algorithm to create randomly generated floor layout
export class Generation {
    std::unique_ptr<Node> root;
    std::vector<Node*> leaves;

    std::vector<Shape> rooms;

    // Dungeon floor layout
    std::string layout;

    // Minimum leaf size before merging leaves to become rooms
    int minLeafSize;
    
    // Maximum leaf size before merging leaves to become rooms
    int maxLeafSize;

    public:
    Generation(int minLeafSize, int maxLeafSize);

    std::string createLayout(int numChambers);
    std::string getLayout() { return layout; }

    private:
    bool divide(Node* node);

    void findNeighbours();

    // Merge leaf with a random neighbour
    void mergeNeighbour(Node& leaf);

    // Attempts to merge leaves until there are no more than maxRooms many leaves
    void merge(int maxRooms);

    // Create binary space partition to create leaves
    void binarySpacePartition(const int numChambers);

    void buildPassages();
    void buildDungeon(int numChambers);
    
    // Checks whether path between two points is clear and ignores the two given nodes
    bool passagePathClear(const std::pair<int, int>& start, const std::pair<int, int>& end, 
                          const Node* skip1, const Node* skip2) const;
};
