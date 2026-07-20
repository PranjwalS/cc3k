export module constants;

import <optional>;
import <utility>;
import <string>;
import <string_view>;
import <array>;
import <set>;
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

        bool isInBounds(const std::pair<int, int> pos);
    }

    namespace colour {
        // Note that colours automatically reset to RESET upon use
        // Base ANSI colours
        constexpr std::string RESET         = "\033[0;0m"; // default text colour
        constexpr std::string BLACK         = "\033[0;30m";
        constexpr std::string RED           = "\033[0;31m";
        constexpr std::string GREEN         = "\033[0;32m";
        constexpr std::string YELLOW        = "\033[0;33m";
        constexpr std::string BLUE          = "\033[0;34m";
        constexpr std::string PURPLE        = "\033[0;35m";
        constexpr std::string CYAN          = "\033[0;36m";
        constexpr std::string WHITE         = "\033[0;37m";

        // Variations
        constexpr std::string DIM_BLACK     = "\033[2;30m";
        constexpr std::string BRIGHT_RED    = "\033[1;31m";
        constexpr std::string DIM_RED       = "\033[2;31m";
        constexpr std::string BRIGHT_GREEN  = "\033[1;32m";
        constexpr std::string DIM_GREEN     = "\033[2;32m";
        constexpr std::string BRIGHT_YELLOW = "\033[1;33m";
        constexpr std::string DIM_YELLOW    = "\033[2;33m";
        constexpr std::string BRIGHT_BLUE   = "\033[1;34m";
        constexpr std::string DIM_BLUE      = "\033[2;34m";
        constexpr std::string DIM_PURPLE    = "\033[0;35m";
        constexpr std::string DIM_WHITE     = "\033[2;37m";


        // Game symbol colours:
        // Player
        constexpr std::string PLAYER = BLUE;

        // Items
        constexpr std::string GOLD = YELLOW;
        constexpr std::string POTION = GREEN;

        // Environment
        constexpr std::string WALL = RESET;
        constexpr std::string FLOOR = RESET;
        constexpr std::string PASSAGE = RESET;
        constexpr std::string DOORWAY = RESET;
        constexpr std::string EMPTY = RESET;
        constexpr std::string STAIRS = BLUE;

        // Enemies
        constexpr std::string HUMAN = RED;
        constexpr std::string DWARF = RED;
        constexpr std::string ELF = RED;
        constexpr std::string ORC = RED;
        constexpr std::string MERCHANT = RED;
        constexpr std::string HALFLING = RED;
        constexpr std::string DRAGON = RED;
    }

    constexpr int NUM_POTIONS = 10;
    constexpr int NUM_GOLD = 10;
    constexpr int NUM_ENEMIES = 20;

    namespace command {
        constexpr std::string FREEZE = "f";
        constexpr std::string RESTART = "r";
        constexpr std::string QUIT = "q";
        constexpr std::string USE_POTION = "u";
        constexpr std::string ATTACK = "a";

        namespace direction {
            constexpr std::string NORTH = "no";
            constexpr std::string SOUTH = "so";
            constexpr std::string EAST = "ea";
            constexpr std::string WEST = "we";
            constexpr std::string NORTH_EAST = "ne";
            constexpr std::string NORTH_WEST = "nw";
            constexpr std::string SOUTH_EAST = "se";
            constexpr std::string SOUTH_WEST = "sw";
        }
        // Player commands stored in Player enum class
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

    constexpr int NUM_ENEMY_RACES = 7;

    struct CharacterInfo {
        std::string name;
        int hp, atk, def;
    };

    const std::unordered_map<PlayerRace, CharacterInfo> PLAYER_DATA = {
        { PlayerRace::Shade, {"Shade", 125, 25, 25} },
        { PlayerRace::Drow, {"Drow", 150, 25, 15} },
        { PlayerRace::Vampire, {"Vampire", 50, 25, 25} },
        { PlayerRace::Troll, {"Troll", 120, 25, 15} },
        { PlayerRace::Goblin, {"Goblin", 110, 15, 20} }
    };

    const std::unordered_map<EnemyRace, CharacterInfo> ENEMY_DATA = {
        { EnemyRace::Human, {"Human", 140, 20, 20} },
        { EnemyRace::Dwarf, {"Dwarf", 100, 20, 30} },
        { EnemyRace::Elf, {"Elf", 140, 30, 10} },
        { EnemyRace::Orc, {"Orc", 180, 30, 25} },
        { EnemyRace::Merchant, {"Merchant", 30, 70, 5} },
        { EnemyRace::Halfling, {"Halfling", 100, 15, 20} },
        { EnemyRace::Dragon, {"Dragon", 150, 20, 20} }
    };

    // Item : Symbol
    enum class Item : char {
        Gold = 'G',
        Potion = 'P'
    };

    namespace symbol {
        constexpr char PLAYER = '@';
        // Enemy symbols stored in Enemy enum class
        // Item symbols stored in Item enum class
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

    // Amount of gold lost when Vampire kills an enemy it is allergic to
    constexpr int VAMPIRE_ALLERGY_GOLD_LOSS = 5;

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

        Count // Number of potion types == 6
    };
    
    constexpr int NUM_POTION_TYPES = static_cast<int>(PotionType::Count);

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
        NO, NE, EA, SE, SO, SW, WE, NW, // Cardinal directions
        Count, // Number of directions == 8
        SELF
    };


    constexpr int NUM_DIRECTIONS = static_cast<int>(Direction::Count);

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

export bool isDirection(const std::string &s);

export std::optional<constants::PlayerRace> cmdToPlayerRace(const std::string &s);
export bool isPlayerRaceCmd(const std::string &s) { return cmdToPlayerRace(s) != std::nullopt; }
export std::optional<std::string> playerRaceToStr(constants::PlayerRace race);

export char itemToSymbol(const constants::Item& i) { return static_cast<char>(i); }

export char enemyRaceToSymbol(const constants::EnemyRace& e) { return static_cast<char>(e); }
export std::optional<constants::EnemyRace> symbolToEnemyRace(const char& c);

export std::string symbolToColour(const char symbol);

export constants::Direction strToDir(const std::string& s);
export std::pair<int, int> dirToPair(const constants::Direction& dir);
export std::pair<int, int> strToPair(const std::string& s);
export std::pair<int, int> operator+(const std::pair<int, int> pos, const constants::Direction dir);
export std::string dirToStr(constants::Direction dir);
export std::string potionTypeToStr(constants::PotionType t);
