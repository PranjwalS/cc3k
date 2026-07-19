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

std::optional<Enemy> symbolToEnemy(const char& c) {
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

std::string symbolToColour(const char symbol) {
    if (symbol == symbol::PLAYER) return colour::PLAYER;
    else if (symbol == symbol::VERTICAL_WALL || 
            symbol == symbol::HORIZONTAL_WALL) return colour::WALL;
    else if (symbol == symbol::DOORWAY) return colour::DOORWAY;
    else if (symbol == symbol::PASSAGE) return colour::PASSAGE;
    else if (symbol == symbol::FLOOR) return colour::FLOOR;
    else if (symbol == itemToSymbol(Item::Gold)) return colour::GOLD;
    else if (symbol == itemToSymbol(Item::Potion)) return colour::POTION;
    else if (symbol == enemyToSymbol(Enemy::Human)) return colour::HUMAN;
    else if (symbol == enemyToSymbol(Enemy::Dwarf)) return colour::DWARF;
    else if (symbol == enemyToSymbol(Enemy::Elf)) return colour::ELF;
    else if (symbol == enemyToSymbol(Enemy::Orc)) return colour::ORC;
    else if (symbol == enemyToSymbol(Enemy::Merchant)) return colour::MERCHANT;
    else if (symbol == enemyToSymbol(Enemy::Halfling)) return colour::HALFLING;
    else if (symbol == enemyToSymbol(Enemy::Dragon)) return colour::DRAGON;
    else return colour::EMPTY;
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

std::string dirToStr(constants::Direction dir) {
    switch(dir) {
        case Direction::NO: return "North";
        case Direction::SO: return "South";
        case Direction::EA: return "East";
        case Direction::WE: return "West";
        case Direction::NE: return "North East";
        case Direction::NW: return "North West";
        case Direction::SE: return "South East";
        case Direction::SW: return "South West";
        default: return "";
    }
}

std::string potionTypeToStr(constants::PotionType t) {
    switch(t) {
        case PotionType::RH: return "RH";
        case PotionType::BA: return "BA";
        case PotionType::BD: return "BD";
        case PotionType::PH: return "PH";
        case PotionType::WA: return "WA";
        case PotionType::WD: return "WD";
        default: return "unknown";
    }
}

std::pair<int, int> strToPair(const std::string& s) {
    return dirToPair(strToDir(s));
}

std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    return {pos.first + dx, pos.second + dy};
}
