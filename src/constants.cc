export module constants;

import <optional>;
import <utility>;
import <string_view>;
import <array>;

// Returns value of key in table of key-value pairs
template <typename Key, typename Value, std::size_t N>
constexpr std::optional<Value> tableLookup(const std::array<std::pair<Key, Value>, N>& table, 
                                           const Key key) {
    for (const auto& [k, v] : table)
        if (k == key) return v;
    return std::nullopt;
}

// Returns key in table of key-value pairs given the value of one member
template <typename Key, typename Value, std::size_t N, typename Field>
constexpr std::optional<Key> reverseLookup(const std::array<std::pair<Key, Value>, N>& table,
                                           Field Value::* member, const Field& value) {
    for (const auto& [k, v] : table)
        if (v.*member == value) return k;
    return std::nullopt;
}

export namespace constants {
    // Board features
    namespace board {
        // Board dimensions
        constexpr int HEIGHT = 25;
        constexpr int WIDTH = 79;

        // Maximum x/y positions: DO NOT MODIFY
        constexpr int MAX_Y = HEIGHT - 1;
        constexpr int MAX_X = WIDTH - 1;
 
        constexpr int NUM_FLOORS = 5;
        constexpr int NUM_CHAMBERS = 5;

        // How far from right to display right alligned entries
        constexpr int OFFSET = 3; 

        constexpr bool isInBounds(int x, int y) {
            return x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y;
        }
    }

    namespace colour {
        // Note that colours automatically reset to RESET upon use
        // Base ANSI colours
        constexpr std::string_view RESET         = "\033[0;0m"; // default text colour
        constexpr std::string_view BLACK         = "\033[0;30m";
        constexpr std::string_view RED           = "\033[0;31m";
        constexpr std::string_view GREEN         = "\033[0;32m";
        constexpr std::string_view YELLOW        = "\033[0;33m";
        constexpr std::string_view BLUE          = "\033[0;34m";
        constexpr std::string_view PURPLE        = "\033[0;35m";
        constexpr std::string_view CYAN          = "\033[0;36m";
        constexpr std::string_view WHITE         = "\033[0;37m";
    }

    constexpr int NUM_POTIONS = 10;
    constexpr int NUM_GOLD = 10;
    constexpr int NUM_ENEMIES = 20;

    namespace command {
        constexpr std::string_view FREEZE = "f";
        constexpr std::string_view RESTART = "r";
        constexpr std::string_view QUIT = "q";
        constexpr std::string_view USE_POTION = "u";
        constexpr std::string_view ATTACK = "a";

        namespace direction {
            constexpr std::string_view NORTH = "no";
            constexpr std::string_view SOUTH = "so";
            constexpr std::string_view EAST = "ea";
            constexpr std::string_view WEST = "we";
            constexpr std::string_view NORTH_EAST = "ne";
            constexpr std::string_view NORTH_WEST = "nw";
            constexpr std::string_view SOUTH_EAST = "se";
            constexpr std::string_view SOUTH_WEST = "sw";
        }

        namespace player {
            constexpr std::string_view SHADE = "s";
            constexpr std::string_view DROW = "d";
            constexpr std::string_view VAMPIRE = "v";
            constexpr std::string_view TROLL = "t";
            constexpr std::string_view GOBLIN = "g";
        }
    }

    namespace symbol {
        constexpr char PLAYER = '@';

        // Enemies
        constexpr char HUMAN = 'H';
        constexpr char DWARF = 'W';
        constexpr char ELF = 'E';
        constexpr char ORC = 'O';
        constexpr char MERCHANT = 'M';
        constexpr char HALFLING = 'L';
        constexpr char DRAGON = 'D';

        // Items
        constexpr char GOLD = 'G';
        constexpr char POTION = 'P';

        // Environment
        constexpr char VERTICAL_WALL = '|';
        constexpr char HORIZONTAL_WALL = '-';
        constexpr char DOORWAY = '+';
        constexpr char PASSAGE = '#';
        constexpr char FLOOR = '.';
        constexpr char STAIRS = '\\';

        constexpr char EMPTY = '\0';
    }

    constexpr std::array SYMBOL_COLOURS = std::to_array<std::pair<char, std::string_view>>({
        { symbol::PLAYER,           colour::BLUE },
        { symbol::HUMAN,            colour::RED },
        { symbol::DWARF,            colour::RED },
        { symbol::ELF,              colour::RED },
        { symbol::ORC,              colour::RED },
        { symbol::MERCHANT,         colour::RED },
        { symbol::HALFLING,         colour::RED },
        { symbol::DRAGON,           colour::RED },
        { symbol::GOLD,             colour::YELLOW },
        { symbol::POTION,           colour::GREEN },
        { symbol::VERTICAL_WALL,    colour::RESET },
        { symbol::HORIZONTAL_WALL,  colour::RESET },
        { symbol::DOORWAY,          colour::RESET },
        { symbol::PASSAGE,          colour::RESET },
        { symbol::FLOOR,            colour::RESET },
        { symbol::STAIRS,           colour::BLUE }
    });

    enum class PlayerRace { Shade, Drow, Vampire, Troll, Goblin };
    enum class EnemyRace { Human, Dwarf, Elf, Orc, Merchant, Halfling, Dragon };

    struct CharacterInfo {
        std::string_view name;
        int hp, atk, def;
    };

    struct PlayerInfo : public CharacterInfo { std::string_view command; };

    constexpr std::array PLAYER_DATA = std::to_array<std::pair<PlayerRace, PlayerInfo>>({
        { PlayerRace::Shade,    {"Shade", 125, 25, 25, command::player::SHADE} },
        { PlayerRace::Drow,     {"Drow", 150, 25, 15, command::player::DROW} },
        { PlayerRace::Vampire,  {"Vampire", 50, 25, 25, command::player::VAMPIRE} },
        { PlayerRace::Troll,    {"Troll", 120, 25, 15, command::player::TROLL} },
        { PlayerRace::Goblin,   {"Goblin", 110, 15, 20, command::player::GOBLIN} }
    });

    constexpr int NUM_PLAYER_RACES = PLAYER_DATA.size();

    // HP gained when a vampire attacks an enemy
    constexpr int VAMPIRE_LIFESTEAL = 5;
    // HP lost when vampire attacks a dwarf
    constexpr int VAMPIRE_ALLERGY_HP_LOSS = 5;
    // HP troll regenerates after every turn
    constexpr int TROLL_REGEN = 5;
    // Gold goblin steals after every slain enemy
    constexpr int GOBLIN_STEAL = 5;

    struct EnemyInfo : public CharacterInfo { char symbol; };

    constexpr std::array ENEMY_DATA = std::to_array<std::pair<EnemyRace, EnemyInfo>>({
        { EnemyRace::Human,     {"Human", 140, 20, 20, symbol::HUMAN} },
        { EnemyRace::Dwarf,     {"Dwarf", 100, 20, 30, symbol::DWARF} },
        { EnemyRace::Elf,       {"Elf", 140, 30, 10, symbol::ELF} },
        { EnemyRace::Orc,       {"Orc", 180, 30, 25, symbol::ORC} },
        { EnemyRace::Merchant,  {"Merchant", 30, 70, 5, symbol::MERCHANT} },
        { EnemyRace::Halfling,  {"Halfling", 100, 15, 20, symbol::HALFLING} },
        { EnemyRace::Dragon,    {"Dragon", 150, 20, 20, symbol::DRAGON} }
    });

    constexpr int NUM_ENEMY_RACES = ENEMY_DATA.size();

    constexpr std::optional<PlayerInfo> info(const PlayerRace race) {
        return tableLookup(PLAYER_DATA, race);
    }

    constexpr std::optional<EnemyInfo> info(const EnemyRace race) {
        return tableLookup(ENEMY_DATA, race);
    }

    enum class Item { Gold, Potion };

    enum class PotionType : int { RH, BA, BD, PH, WA, WD };

    struct PotionInfo {
        std::string_view name;
        int hpMod, atkMod, defMod;
        bool permanent;
    };

    constexpr std::array POTION_DATA = std::to_array<std::pair<PotionType, PotionInfo>>({
        { PotionType::RH,   {"RH", 10, 0, 0, true} },
        { PotionType::BA,   {"BA", 0, 5, 0, false} },
        { PotionType::BD,   {"BD", 0, 0, 5, false} },
        { PotionType::PH,   {"PH", -10, 0, 0, true} },
        { PotionType::WA,   {"WA", 0, 5, 0, false} },
        { PotionType::WD,   {"WD", 0, 0, -5, false} }
    });

    constexpr int NUM_POTION_TYPES = POTION_DATA.size();

    constexpr std::optional<PotionInfo> info(const PotionType type) {
        return tableLookup(POTION_DATA, type);
    }

    // Amount of gold in each type of pile
    namespace goldPile {
        constexpr int SMALL = 1;
        constexpr int NORMAL = 2;
        constexpr int MERCHANT_HOARD = 4;
        constexpr int DRAGON_HOARD = 6;
    }

    namespace probability {
        namespace spawn {
            // Enemy rates
            struct WeightedEnemy {
                const EnemyRace race;
                const double probability;
            };

            constexpr std::array ENEMIES = std::to_array<WeightedEnemy>({
                { EnemyRace::Human, 2.0 / 9.0 },
                { EnemyRace::Dwarf, 3.0 / 18.0 },
                { EnemyRace::Halfling, 5.0 / 18.0 },
                { EnemyRace::Elf, 1.0 / 9.0 },
                { EnemyRace::Orc, 1.0 / 9.0 },
                { EnemyRace::Merchant, 1.0 / 9.0 }
            });

            constexpr int NUM_WEIGHTED_ENEMIES = ENEMIES.size(); 

            // Gold rates
            struct WeightedGold {
                const int goldPile;
                const double probability;
            };

            constexpr std::array GOLD = std::to_array<WeightedGold>({
                { goldPile::NORMAL, 5.0 / 8.0 },
                { goldPile::DRAGON_HOARD, 1.0 / 8.0 },
                { goldPile::SMALL, 1.0 / 4.0 }
            });

            constexpr int NUM_WEIGHTED_GOLD = GOLD.size();
        }
        constexpr double ENEMY_MISS = 0.5;
        constexpr double HALFLING_EVASION = 0.5;
        
        // Probability an enemy that is not a dragon, human, or merchant drops a normal
        // pile of gold as opposed to a small pile of gold.
        constexpr double GOLD_LUCK = 0.5;
    }

    namespace multiplier {
        constexpr double ORC_ATTACK_GOBLIN = 1.5;
        constexpr double SHADE_SCORE = 1.5;
        constexpr double DROW_POTION = 1.5;
    }

    enum class Direction : int { 
        NO, NE, EA, SE, SO, SW, WE, NW,
        SELF
    };

    struct DirectionInfo {
        std::string_view command;
        std::string_view string;
        std::pair<int, int> pair;
    };

    constexpr std::array DIRECTION_DATA = std::to_array<std::pair<Direction, DirectionInfo>>({
        { Direction::NO, { command::direction::NORTH,       "North",        {0, -1}  }},
        { Direction::EA, { command::direction::EAST,        "East",         {1, 0}   }},
        { Direction::SO, { command::direction::SOUTH,       "South",        {0, 1}   }},
        { Direction::WE, { command::direction::WEST,        "West",         {-1, 0}  }},
        { Direction::NE, { command::direction::NORTH_EAST,  "North East",   {1, -1}  }},
        { Direction::NW, { command::direction::NORTH_WEST,  "North West",   {-1, -1} }},
        { Direction::SE, { command::direction::SOUTH_EAST,  "South East",   {1, 1}   }},
        { Direction::SW, { command::direction::SOUTH_WEST,  "South West",   {-1, 1}  }}
    });

    constexpr int NUM_DIRECTIONS = DIRECTION_DATA.size();

    constexpr std::optional<DirectionInfo> info(const Direction dir) {
        return tableLookup(DIRECTION_DATA, dir);
    }

    constexpr std::string_view EMPTY_FLOOR = 
    "|-----------------------------------------------------------------------------|"
    "|                                                                             |"
    "| |--------------------------|        |-----------------------|               |"
    "| |..........................|        |.......................|               |"
    "| |..........................+########+.......................|-------|       |"
    "| |..........................|   #    |...............................|--|    |"
    "| |..........................|   #    |..................................|--| |"
    "| |----------+---------------|   #    |----+----------------|...............| |"
    "|            #                 #############                |...............| |"
    "|            #                 #     |-----+------|         |...............| |"
    "|            #                 #     |............|         |...............| |"
    "|            ###################     |............|   ######+...............| |"
    "|            #                 #     |............|   #     |...............| |"
    "|            #                 #     |-----+------|   #     |--------+------| |"
    "|  |---------+-----------|     #           #          #              #        |"
    "|  |.....................|     #           #          #         |----+------| |"
    "|  |.....................|     ########################         |...........| |"
    "|  |.....................|     #           #                    |...........| |"
    "|  |.....................|     #    |------+--------------------|...........| |"
    "|  |.....................|     #    |.......................................| |"
    "|  |.....................+##########+.......................................| |"
    "|  |.....................|          |.......................................| |"
    "|  |---------------------|          |---------------------------------------| |"
    "|                                                                             |"
    "|-----------------------------------------------------------------------------|";
}

using namespace constants;

export constexpr std::string_view symbolToColour(const char sym) {
    auto col = tableLookup(SYMBOL_COLOURS, sym);
    return col ? *col : colour::RESET;
}

export constexpr std::optional<PlayerRace> cmdToPlayerRace(std::string_view s) {
    return reverseLookup(PLAYER_DATA, &PlayerInfo::command, s);
}

export constexpr bool isPlayerRaceCmd(std::string_view s) {
    return cmdToPlayerRace(s) != std::nullopt; 
}

export constexpr std::string_view playerRaceToStr(const PlayerRace race) {
    auto data = info(race);
    return data ? data->name : "";
}

export constexpr std::string_view potionTypeToStr(const PotionType t) {
    auto data = info(t);
    return data ? data->name : "unknown";
}

export constexpr char enemyRaceToSymbol(const EnemyRace race) { return info(race)->symbol; }

export constexpr std::optional<EnemyRace> symbolToEnemyRace(const char c) {
    return reverseLookup(ENEMY_DATA, &EnemyInfo::symbol, c);
}

export constexpr bool isEnemySymbol(const char c) {
    return symbolToEnemyRace(c) != std::nullopt;
}

export constexpr Direction cmdToDir(std::string_view s) {
    auto dir = reverseLookup(DIRECTION_DATA, &DirectionInfo::command, s);
    return dir ? *dir : Direction::SELF;
}

export constexpr bool isDirection(std::string_view s) {
    return cmdToDir(s) != Direction::SELF;
}

export constexpr std::pair<int, int> dirToPair(const Direction dir) {
    auto data = info(dir);
    return data ? data->pair : std::pair{0, 0};
}

export constexpr std::string_view dirToStr(const Direction dir) {
    auto data = info(dir);
    return data ? data->string : "";
}

export constexpr std::pair<int, int> operator+(const std::pair<int, int> pos, 
                                               const Direction dir) {
    auto [dx, dy] = dirToPair(dir);
    return {pos.first + dx, pos.second + dy};
}
