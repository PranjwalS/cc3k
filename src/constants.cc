export module constants;

import <optional>;
import <utility>;
import <string>;
import <string_view>;
import <array>;
import <unordered_map>;

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

        // Game symbol colours:
        // Player
        constexpr std::string_view PLAYER = BLUE;

        // Items
        constexpr std::string_view GOLD = YELLOW;
        constexpr std::string_view POTION = GREEN;

        // Environment
        constexpr std::string_view WALL = RESET;
        constexpr std::string_view FLOOR = RESET;
        constexpr std::string_view PASSAGE = RESET;
        constexpr std::string_view DOORWAY = RESET;
        constexpr std::string_view EMPTY = RESET;
        constexpr std::string_view STAIRS = BLUE;

        // Enemies
        constexpr std::string_view HUMAN = RED;
        constexpr std::string_view DWARF = RED;
        constexpr std::string_view ELF = RED;
        constexpr std::string_view ORC = RED;
        constexpr std::string_view MERCHANT = RED;
        constexpr std::string_view HALFLING = RED;
        constexpr std::string_view DRAGON = RED;
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
        // Player commands stored in PlayerRace enum class
    }

    // Player Races : Command
    enum class PlayerRace : char {
        Shade='s',
        Drow='d',
        Vampire='v',
        Troll='t',
        Goblin='g'
    };

    constexpr int NUM_PLAYER_RACES = 5;

    // Enemy Races : Symbol
    enum class EnemyRace : char {
        Human = 'H',
        Dwarf = 'W',
        Elf = 'E',
        Orc = 'O',
        Merchant = 'M',
        Dragon = 'D',
        Halfling = 'L'
    };
    constexpr char enemyRaceToSymbol(const EnemyRace e) { return static_cast<char>(e); }

    constexpr int NUM_ENEMY_RACES = 7;

    struct CharacterInfo {
        std::string_view name;
        int hp, atk, def;
    };

    const std::unordered_map<PlayerRace, CharacterInfo> PLAYER_DATA = {
        { PlayerRace::Shade,    {"Shade", 125, 25, 25} },
        { PlayerRace::Drow,     {"Drow", 150, 25, 15} },
        { PlayerRace::Vampire,  {"Vampire", 50, 25, 25} },
        { PlayerRace::Troll,    {"Troll", 120, 25, 15} },
        { PlayerRace::Goblin,   {"Goblin", 110, 15, 20} }
    };

    const std::unordered_map<EnemyRace, CharacterInfo> ENEMY_DATA = {
        { EnemyRace::Human,     {"Human", 140, 20, 20} },
        { EnemyRace::Dwarf,     {"Dwarf", 100, 20, 30} },
        { EnemyRace::Elf,       {"Elf", 140, 30, 10} },
        { EnemyRace::Orc,       {"Orc", 180, 30, 25} },
        { EnemyRace::Merchant,  {"Merchant", 30, 70, 5} },
        { EnemyRace::Halfling,  {"Halfling", 100, 15, 20} },
        { EnemyRace::Dragon,    {"Dragon", 150, 20, 20} }
    };

    // Item : Symbol
    enum class Item : char {
        Gold = 'G',
        Potion = 'P'
    };
    constexpr char itemToSymbol(const Item i) { return static_cast<char>(i); }

    namespace symbol {
        constexpr char PLAYER = '@';

        // Enemies
        constexpr char HUMAN = enemyRaceToSymbol(EnemyRace::Human);
        constexpr char DWARF = enemyRaceToSymbol(EnemyRace::Dwarf);
        constexpr char ELF = enemyRaceToSymbol(EnemyRace::Elf);
        constexpr char ORC = enemyRaceToSymbol(EnemyRace::Orc);
        constexpr char MERCHANT = enemyRaceToSymbol(EnemyRace::Merchant);
        constexpr char HALFLING = enemyRaceToSymbol(EnemyRace::Halfling);
        constexpr char DRAGON = enemyRaceToSymbol(EnemyRace::Dragon);

        // Items
        constexpr char GOLD = itemToSymbol(Item::Gold);
        constexpr char POTION = itemToSymbol(Item::Potion);

        // Environment
        constexpr char VERTICAL_WALL = '|';
        constexpr char HORIZONTAL_WALL = '-';
        constexpr char DOORWAY = '+';
        constexpr char PASSAGE = '#';
        constexpr char FLOOR = '.';
        constexpr char STAIRS = '\\';

        constexpr char EMPTY = '\0';
    }

    // Amount of gold in each type of pile
    namespace goldPile {
        constexpr int SMALL = 1;
        constexpr int NORMAL = 2;
        constexpr int MERCHANT_HOARD = 4;
        constexpr int DRAGON_HOARD = 6;
    }

    // Player behaviour constants
    // HP gained when a vampire attacks an enemy
    constexpr int VAMPIRE_LIFESTEAL = 5;
    // HP lost when vampire attacks a dwarf
    constexpr int VAMPIRE_ALLERGY_HP_LOSS = 5;
    // HP troll regenerates after every turn
    constexpr int TROLL_REGEN = 5;
    // Gold goblin steals after every slain enemy
    constexpr int GOBLIN_STEAL = 5;

    // Potion Type : int value
    enum class PotionType : int { 
        // Positive Potions:
        RH, // Restore health: Restore up to 10 HP
        BA, // Boost Atk: Increase ATK by 5
        BD, // Boost Def: Increase Def by 5

        // Negative Potions:
        PH, // Poison health: Lose up to 10 HP
        WA, // Wound Atk: Decrease Atk by 5
        WD, // Wound Def: Decrease Def by 5
    };
    
    constexpr int NUM_POTION_TYPES = 6;

    struct PotionInfo {
        std::string_view name;
        int hpMod, atkMod, defMod;
        bool permanent;
    };

    const std::unordered_map<PotionType, PotionInfo> POTION_DATA = {
        { PotionType::RH,   {"RH", 10, 0, 0, true} },
        { PotionType::BA,   {"BA", 0, 5, 0, false} },
        { PotionType::BD,   {"BD", 0, 0, 5, false} },
        { PotionType::PH,   {"PH", -10, 0, 0, true} },
        { PotionType::WA,   {"WA", 0, 5, 0, false} },
        { PotionType::WD,   {"WD", 0, 0, -5, false} }
    };

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

            // Note: std::array::size() is determined at compile time -> this is valid
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

            constexpr int NUM_WEIGHTED_GOLD = GOLD.size(); // determined at compile time
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

    // Direction : int value
    enum class Direction : int { 
        NO, NE, EA, SE, SO, SW, WE, NW,
        SELF
    };

    constexpr int NUM_DIRECTIONS = 8;

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

export bool isDirection(std::string_view s);

export std::optional<PlayerRace> cmdToPlayerRace(std::string_view s);
export bool isPlayerRaceCmd(std::string_view s);
export std::optional<std::string> playerRaceToStr(const PlayerRace race);

export std::optional<EnemyRace> symbolToEnemyRace(const char c);

export std::string symbolToColour(const char sym);

export Direction cmdToDir(std::string_view s);
export std::pair<int, int> dirToPair(const Direction dir);
export std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir);
export std::string dirToStr(const Direction dir);
export std::string potionTypeToStr(const PotionType t);
