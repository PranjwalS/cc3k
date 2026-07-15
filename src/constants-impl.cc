module constants;
import <optional>;
import <utility>;
import <string>;

bool constants::board::isInBounds(const std::pair<int, int> pos) {
    return pos.first >= 0 && pos.first <= MAX_X && pos.second >= 0 && pos.second <= MAX_Y;
}

using namespace constants;

bool isDirection(const std::string &s) {
    return strToDir(s) != Direction::SELF;
}

std::optional<Player> cmdToPlayer(const std::string &s) {
    if (s.size() != 1) return std::nullopt;
    const Player race = static_cast<Player>(s.at(0));

    switch (race) {
        case Player::Shade:
        case Player::Drow:
        case Player::Vampire:
        case Player::Troll:
        case Player::Goblin:
            return race;
        default:
            return std::nullopt; // Invalid player race command
    }
}

std::optional<std::string> playerToStr(constants::Player race) {
    switch (race) {
        case Player::Shade: return "Shade";
        case Player::Drow: return "Drow";
        case Player::Vampire: return "Vampire";
        case Player::Troll: return "Troll";
        case Player::Goblin: return "Goblin";
        default: return std::nullopt; // Invalid player race
    }
}

std::optional<Enemy> charToEnemy(const char& c) {
    const Enemy race = static_cast<Enemy>(c);
    
    switch (race) {
        case Enemy::Human:
        case Enemy::Dwarf:
        case Enemy::Elf: 
        case Enemy::Orc: 
        case Enemy::Merchant: 
        case Enemy::Dragon: 
        case Enemy::Halfling:
            return race;
        default:
            return std::nullopt; // Invalid enemy character
    }
}

Direction strToDir(const std::string& s) {
    if (s == command::direction::NORTH) return Direction::NO;
    if (s == command::direction::SOUTH) return Direction::SO;
    if (s == command::direction::EAST) return Direction::EA;
    if (s == command::direction::WEST) return Direction::WE;
    if (s == command::direction::NORTH_EAST) return Direction::NE;
    if (s == command::direction::NORTH_WEST) return Direction::NW;
    if (s == command::direction::SOUTH_EAST) return Direction::SE;
    if (s == command::direction::SOUTH_WEST) return Direction::SW;
    return Direction::SELF;
}

std::pair<int, int> dirToPair(const Direction& dir) {
    if (dir == Direction::NO) return {0, -1};
    if (dir == Direction::SO) return {0, 1};
    if (dir == Direction::EA) return {1, 0};
    if (dir == Direction::WE) return {-1, 0};
    if (dir == Direction::NE) return {1, -1};
    if (dir == Direction::NW) return {-1, -1};
    if (dir == Direction::SE) return {1, 1};
    if (dir == Direction::SW) return {-1, 1};
    return {0, 0};
}

std::pair<int, int> strToPair(const std::string& s) {
    return dirToPair(strToDir(s));
}

std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    return {pos.first + dx, pos.second + dy};
}
