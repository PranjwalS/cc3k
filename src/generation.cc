export module generation;
import shapes;
import random;
import constants;
import <utility>;
import <vector>;
import <optional>;
import <memory>;
import <string>;

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

export class Generation {
    std::unique_ptr<Node> root;
    std::vector<Node*> leaves;

    std::vector<Shape> rooms;

    std::string layout;

    int minLeafSize;
    int maxLeafSize;
    int roomPadding = constants::generation::ROOM_PADDING;

    public:
    Generation(int minLeafSize, int maxLeafSize);

    std::string createLayout(int numChambers);
    std::string getLayout() { return layout; }

    private:
    bool divide(Node* node);

    void findNeighbours();
    void mergeNeighbour(Node& leaf);
    void merge(int maxRooms);

    void binarySpacePartition(const int numChambers);
    void buildPassages();
    void buildDungeon(int numChambers);
};
