export module constants;

import <optional>;
import <utility>;
import <string>;
import <string_view>;

export namespace constants {
    // Board features
    namespace board {
        // Board dimensions
        constexpr int HEIGHT{25};
        constexpr int WIDTH{79};

        // Maximum x/y positions: DO NOT MODIFY
        constexpr int MAX_Y = HEIGHT - 1;
        constexpr int MAX_X = WIDTH - 1;

        constexpr int NUM_FLOORS = 5;
        constexpr int NUM_CHAMBERS = 5;

        bool isInBounds(const std::pair<int, int> pos);
    }
    
    constexpr int NUM_POTIONS = 10;
    constexpr int NUM_GOLD = 10;
    constexpr int NUM_ENEMIES = 20;

    constexpr char PLAYER_CHAR = '@';

    enum class Player : char;

    namespace command {
        constexpr std::string FREEZE = "f";
        constexpr std::string RESTART = "r";
        constexpr std::string QUIT = "q";
        constexpr std::string USE = "u";
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
        bool isDirection(const std::string &s);

        std::optional<Player> toPlayerRace(const std::string &s);
        bool isPlayerRace(const std::string &s);
    }

    // Player Races : Command
    enum class Player : char {
        Shade='s',
        Drow='d',
        Vampire='v',
        Troll='t',
        Goblin='g',

        Count
    };

    constexpr int NUM_PLAYER_RACES = static_cast<int>(Player::Count);

    // Enemy Races : Symbol
    enum class Enemy : char {
        Human = 'H',
        Dwarf = 'W',
        Elf = 'E',
        Orc = 'O',
        Merchant = 'M',
        Dragon = 'D',
        Halfling = 'L',

        Count
    };

    constexpr int NUM_ENEMY_RACES = static_cast<int>(Enemy::Count);

    char enemyToChar(const Enemy& e) { return static_cast<char>(e); }

    std::optional<Enemy> charToEnemy(const char& c);

    // Item : Symbol
    enum class Item : char {
        Gold = 'G',
        Potion = 'P'
    };

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
                const Enemy race;
                const double probability;
            };

            constexpr WeightedEnemy ENEMIES[] = {
                { Enemy::Human, 2.0 / 9.0 },
                { Enemy::Dwarf, 3.0 / 18.0 },
                { Enemy::Halfling, 5.0 / 18.0 },
                { Enemy::Elf, 1.0 / 9.0 },
                { Enemy::Orc, 1.0 / 9.0 },
                { Enemy::Merchant, 1.0 / 9.0 }
            };

            constexpr int NUM_WEIGHTED_ENEMIES = 6;

            // Gold rates
            struct WeightedGold {
                const int goldPile;
                const double probability;
            };

            constexpr WeightedGold GOLD[] = {
                { goldPile::NORMAL, 5.0 / 8.0 },
                { goldPile::DRAGON_HOARD, 1.0 / 8.0 },
                { goldPile::SMALL, 1.0 / 4.0 },
            };

            constexpr int NUM_WEIGHTED_GOLD = 3;
        }
        constexpr double ENEMY_MISS = 0.5;
        constexpr double HALFLING_EVASION = 0.5;
        
        // Probability an enemy that is not a dragon, human, or merchant drops a normal
        // pile of gold as opposed to a small pile of gold.
        constexpr double GOLD_LUCK = 0.5;
    }

    // Direction : int value
    enum class Direction : int { 
        NO, NE, EA, SE, SO, SW, WE, NW, // Cardinal directions
        Count, // Number of directions == 8
        SELF
    };

    constexpr int NUM_DIRECTIONS = static_cast<int>(Direction::Count);

    Direction strToDir(const std::string& s);
    std::pair<int, int> dirToPair(const Direction& dir);
    std::pair<int, int> strToPair(const std::string& s);
    std::pair<int, int> operator+(const std::pair<int, int> pos, const Direction dir);

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
