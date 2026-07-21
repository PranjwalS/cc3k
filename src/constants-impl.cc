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
    return cmdToDir(s) != Direction::SELF;
}

std::optional<PlayerRace> cmdToPlayerRace(const std::string &s) {
    if (s.size() != 1) return std::nullopt;
    const PlayerRace race = static_cast<PlayerRace>(s.at(0));

    if (PLAYER_DATA.contains(race)) return race;
    return std::nullopt; // Invalid player race command
}

bool isPlayerRaceCmd(const std::string &s) { 
    return cmdToPlayerRace(s) != std::nullopt; 
}

std::optional<std::string> playerRaceToStr(const constants::PlayerRace race) {
    if (PLAYER_DATA.contains(race)) return PLAYER_DATA.at(race).name;
    return std::nullopt; // Invalid player race
}

std::optional<EnemyRace> symbolToEnemyRace(const char c) {
    const EnemyRace race = static_cast<EnemyRace>(c);
    if (ENEMY_DATA.contains(race)) return race;
    return std::nullopt; // Invalid enemy race
}

std::string symbolToColour(const char symbol) {
    switch (symbol) {
        case symbol::PLAYER:            return colour::PLAYER;
        case symbol::VERTICAL_WALL:
        case symbol::HORIZONTAL_WALL:   return colour::WALL;
        case symbol::DOORWAY:           return colour::DOORWAY;
        case symbol::PASSAGE:           return colour::PASSAGE;
        case symbol::FLOOR:             return colour::FLOOR;
        case symbol::STAIRS:            return colour::STAIRS;
        case symbol::GOLD:              return colour::GOLD;
        case symbol::POTION:            return colour::POTION;
        case symbol::HUMAN:             return colour::HUMAN;
        case symbol::DWARF:             return colour::DWARF;
        case symbol::ELF:               return colour::ELF;
        case symbol::ORC:               return colour::ORC;
        case symbol::MERCHANT:          return colour::MERCHANT;
        case symbol::HALFLING:          return colour::HALFLING;
        case symbol::DRAGON:            return colour::DRAGON;
        default:                        return colour::EMPTY;
    }
}

Direction cmdToDir(const std::string& s) {
    if (s == command::direction::NORTH)      return Direction::NO;
    if (s == command::direction::SOUTH)      return Direction::SO;
    if (s == command::direction::EAST)       return Direction::EA;
    if (s == command::direction::WEST)       return Direction::WE;
    if (s == command::direction::NORTH_EAST) return Direction::NE;
    if (s == command::direction::NORTH_WEST) return Direction::NW;
    if (s == command::direction::SOUTH_EAST) return Direction::SE;
    if (s == command::direction::SOUTH_WEST) return Direction::SW;
    return  Direction::SELF;
}

std::pair<int, int> dirToPair(const Direction dir) {
    switch (dir) {
        case Direction::NO:  return {0, -1};
        case Direction::SO:  return {0, 1};
        case Direction::EA:  return {1, 0};
        case Direction::WE:  return {-1, 0};
        case Direction::NE:  return {1, -1};
        case Direction::NW:  return {-1, -1};
        case Direction::SE:  return {1, 1};
        case Direction::SW:  return {-1, 1};
        default:             return {0, 0};
    }
}

std::string dirToStr(const constants::Direction dir) {
    switch(dir) {
        case Direction::NO: return "North";
        case Direction::SO: return "South";
        case Direction::EA: return "East";
        case Direction::WE: return "West";
        case Direction::NE: return "North East";
        case Direction::NW: return "North West";
        case Direction::SE: return "South East";
        case Direction::SW: return "South West";
        default:            return "";
    }
}

std::string potionTypeToStr(const constants::PotionType t) {
    if (POTION_DATA.contains(t)) return POTION_DATA.at(t).name;
    return "unkown"; // Invalid potion
}

std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    return {pos.first + dx, pos.second + dy};
}
