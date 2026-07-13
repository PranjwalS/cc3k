export module constants;

import random;
import <optional>;
import <string>;


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
    }
    
    constexpr int NUM_POTIONS = 10;
    constexpr int NUM_ENEMIES = 20;

    constexpr char PLAYER_CHAR = '@';

    enum class Player : char {
        Shade='s',
        Drow='d',
        Vampire='v',
        Troll='t',
        Goblin='g',
    };

    enum class Enemy : char {
        Human = 'H',
        Dwarf = 'W',
        Elf = 'E',
        Orc = 'O',
        Merchant = 'M',
        Dragon = 'D',
        Halfling = 'L'
    };

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

    constexpr int VAMPIRE_ALLERGY_GOLD_LOSS = 5;
    
    enum class PotionType : int { 
        // Positive Potions:
        RH, // Restore health: Restore up to 10 HP
        BA, // Boost Atk: Increase ATK by 5
        BD, // Boost Def: Increase Def by 5
        // Negative Potions:
        PH, // Poison health: Lose up to 10 HP
        WA, // Wound Atk: Decrease Atk by 5
        WD, // Wound Def: Decrease Def by 5

        Count // == 6 automatically
    };
    
    constexpr int NUM_POTION_TYPES = static_cast<int>(PotionType::Count);

    PotionType randomPotion() {
        return static_cast<PotionType>(
            randomNum(0, static_cast<int>(PotionType::Count) - 1)
        );
    }

    namespace probability {
        namespace spawn {
            // Enemy rates
            constexpr double HUMAN = 2.0 / 9.0;
            constexpr double DWARF = 3.0 / 18.0;
            constexpr double HALFLING = 5.0 / 18.0;
            constexpr double ELF = 1.0 / 9.0;
            constexpr double ORC = 1.0 / 9.0;
            constexpr double MERCHANT = 1.0 / 9.0;
        }
        constexpr double ENEMY_MISS = 0.5;
        constexpr double HALFLING_EVASION = 0.5;
        
        // Probability an enemy that is not a dragon, human, or merchant drops a normal
        // pile of gold as opposed to a small pile of gold.
        constexpr double GOLD_LUCK = 0.5;
    }

    constexpr char enemyToChar(const Enemy& e) { return static_cast<char>(e); }

    constexpr std::optional<Enemy> charToEnemy(const char& c) {
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

    enum class Direction : int {
        NO, // == 0
        NE, // == 1
        EA, // ...
        SE, 
        SO, 
        SW, 
        WE, 
        NW, 
        Count, // == 8
        SELF // == 9
    };

    int NUM_DIRECTIONS = static_cast<int>(Direction::Count);

    constexpr Direction strToDir(const std::string& s) {
        if (s == "no") return Direction::NO;
        if (s == "ne") return Direction::SO;
        if (s == "ea") return Direction::EA;
        if (s == "se") return Direction::WE;
        if (s == "so") return Direction::NE;
        if (s == "sw") return Direction::NW;
        if (s == "we") return Direction::SE;
        if (s == "nw") return Direction::SW;
        return Direction::SELF;
    }

    constexpr std::pair<int, int> dirToPair(const Direction& dir) {
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

    constexpr std::pair<int, int> strToPair(const std::string& s) {
        return dirToPair(strToDir(s));
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
