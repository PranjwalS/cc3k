export module generation;
import shapes;
import random;
import constants;
import <utility>;
import <vector>;
import <stdexcept>;
import <optional>;
import <memory>;
import <algorithm>;
import <string_view>;

struct Node {
    int leftX, rightX;
    int topY, bottomY;
    
    int width, height;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    
    std::vector<const Node*> horNeighbours;
    std::vector<const Node*> vertNeighbours;

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

    void addPassage(int x1, int x2, int y1, int y2, Node& neighbour);
};

export class Generation {
    std::unique_ptr<Node> root;
    std::vector<Node*> leaves;

    std::vector<Shape> rooms;

    int minLeafSize;
    int maxLeafSize;
    int roomPadding = 1;
    int gridSize = 1;

    public:
    Generation(int minLeafSize, int maxLeafSize,
               int width = constants::board::WIDTH, int height = constants::board::HEIGHT) : 
        minLeafSize{minLeafSize}, maxLeafSize{maxLeafSize} {
        root = std::make_unique<Node>(0, width, 0, height);
    }

    std::string_view createLayout(int numChambers = constants::board::NUM_CHAMBERS);

    private:
    bool divide(Node* node);

    void findNeighbours();
    void mergeNeighbour(Node& leaf);
    void merge(int maxRooms);

    void binarySpacePartition(const int numChambers);
    void buildPassages();
    void buildDungeon(int numChambers);
};
