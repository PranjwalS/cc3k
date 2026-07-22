module constants;
import <optional>;
import <utility>;
import <string>;
import <string_view>;

using namespace constants;

bool isDirection(std::string_view s) {
    return cmdToDir(s) != Direction::SELF;
}

std::optional<PlayerRace> cmdToPlayerRace(std::string_view s) {
    if (s.size() != 1) return std::nullopt;
    const PlayerRace race = static_cast<PlayerRace>(s.at(0));

    if (PLAYER_DATA.contains(race)) return race;
    return std::nullopt; // Invalid player race command
}

bool isPlayerRaceCmd(std::string_view s) { 
    return cmdToPlayerRace(s) != std::nullopt; 
}

std::optional<std::string> playerRaceToStr(const constants::PlayerRace race) {
    if (PLAYER_DATA.contains(race)) return std::string(PLAYER_DATA.at(race).name);
    return std::nullopt; // Invalid player race
}

std::optional<EnemyRace> symbolToEnemyRace(const char c) {
    const EnemyRace race = static_cast<EnemyRace>(c);
    if (ENEMY_DATA.contains(race)) return race;
    return std::nullopt; // Invalid enemy race
}

std::string symbolToColour(const char sym) {
    std::string_view col = colour::EMPTY;
    switch (sym) {
        case symbol::PLAYER:            col = colour::PLAYER; break;
        case symbol::VERTICAL_WALL:
        case symbol::HORIZONTAL_WALL:   col =  colour::WALL; break;
        case symbol::DOORWAY:           col =  colour::DOORWAY; break;
        case symbol::PASSAGE:           col =  colour::PASSAGE; break;
        case symbol::FLOOR:             col =  colour::FLOOR; break;
        case symbol::STAIRS:            col =  colour::STAIRS; break;
        case symbol::GOLD:              col =  colour::GOLD; break;
        case symbol::POTION:            col =  colour::POTION; break;
        case symbol::HUMAN:             col =  colour::HUMAN; break;
        case symbol::DWARF:             col =  colour::DWARF; break;
        case symbol::ELF:               col =  colour::ELF; break;
        case symbol::ORC:               col =  colour::ORC; break;
        case symbol::MERCHANT:          col =  colour::MERCHANT; break;
        case symbol::HALFLING:          col =  colour::HALFLING; break;
        case symbol::DRAGON:            col =  colour::DRAGON; break;
        default:                        break;
    }
    return std::string(col);
}

Direction cmdToDir(std::string_view s) {
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
    if (POTION_DATA.contains(t)) return std::string(POTION_DATA.at(t).name);
    return "unknown"; // Invalid potion
}

std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    return {pos.first + dx, pos.second + dy};
}
