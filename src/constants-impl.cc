module constants;
import <optional>;
import <utility>;
import <string>;
import <map>;

bool constants::board::isInBounds(const std::pair<int, int> pos) {
    return pos.first >= 0 && pos.first <= MAX_X && pos.second >= 0 && pos.second <= MAX_Y;
}

using namespace constants;

bool isDirection(const std::string &s) {
    return strToDir(s) != Direction::SELF;
}

std::optional<PlayerRace> cmdToPlayerRace(const std::string &s) {
    if (s.size() != 1) return std::nullopt;
    const PlayerRace race = static_cast<PlayerRace>(s.at(0));

    switch (race) {
        case PlayerRace::Shade:
        case PlayerRace::Drow:
        case PlayerRace::Vampire:
        case PlayerRace::Troll:
        case PlayerRace::Goblin:
            return race;
        default:
            return std::nullopt; // Invalid player race command
    }
}

std::optional<std::string> playerRaceToStr(constants::PlayerRace race) {
    switch (race) {
        case PlayerRace::Shade: return "Shade";
        case PlayerRace::Drow: return "Drow";
        case PlayerRace::Vampire: return "Vampire";
        case PlayerRace::Troll: return "Troll";
        case PlayerRace::Goblin: return "Goblin";
        default: return std::nullopt; // Invalid player race
    }
}

std::optional<EnemyRace> symbolToEnemyRace(const char& c) {
    const EnemyRace race = static_cast<EnemyRace>(c);
    
    switch (race) {
        case EnemyRace::Human:
        case EnemyRace::Dwarf:
        case EnemyRace::Elf: 
        case EnemyRace::Orc: 
        case EnemyRace::Merchant: 
        case EnemyRace::Dragon: 
        case EnemyRace::Halfling:
            return race;
        default:
            return std::nullopt; // Invalid enemy race
    }
}

std::string symbolToColour(const char symbol) {
    if (symbol == symbol::PLAYER) return colour::PLAYER;
    else if (symbol == symbol::VERTICAL_WALL || 
            symbol == symbol::HORIZONTAL_WALL) return colour::WALL;
    else if (symbol == symbol::DOORWAY) return colour::DOORWAY;
    else if (symbol == symbol::PASSAGE) return colour::PASSAGE;
    else if (symbol == symbol::FLOOR) return colour::FLOOR;
    else if (symbol == symbol::STAIRS) return colour::STAIRS;
    else if (symbol == itemToSymbol(Item::Gold)) return colour::GOLD;
    else if (symbol == itemToSymbol(Item::Potion)) return colour::POTION;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Human)) return colour::HUMAN;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Dwarf)) return colour::DWARF;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Elf)) return colour::ELF;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Orc)) return colour::ORC;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Merchant)) return colour::MERCHANT;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Halfling)) return colour::HALFLING;
    else if (symbol == enemyRaceToSymbol(EnemyRace::Dragon)) return colour::DRAGON;
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
