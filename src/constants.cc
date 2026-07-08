export module constants;

import <optional>;
import <string>;

export namespace constants {
    // Board features
    namespace board {
        // Board dimensions
        constexpr int HEIGHT{79};
        constexpr int WIDTH{25};

        // Maximum x/y positions: DO NOT MODIFY
        constexpr int MAX_Y = HEIGHT - 1;
        constexpr int MAX_X = WIDTH - 1;
    }
    
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
        NO, NE, EA, SE, SO, SW, WE, NW, SELF 
    };

    constexpr int NUM_DIRECTIONS = 8;

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

    constexpr std::pair<int, int> toDir(const std::string& s) {
        return dirToPair(strToDir(s));
    }

    constexpr std::string_view EMPTY_FLOOR = 
    "|-----------------------------------------------------------------------------|\n"
    "|                                                                             |\n"
    "| |--------------------------|        |-----------------------|               |\n"
    "| |..........................|        |.......................|               |\n"
    "| |..........................+########+.......................|-------|       |\n"
    "| |..........................|   #    |...............................|--|    |\n"
    "| |..........................|   #    |..................................|--| |\n"
    "| |----------+---------------|   #    |----+----------------|...............| |\n"
    "|            #                 #############                |...............| |\n"
    "|            #                 #     |-----+------|         |...............| |\n"
    "|            #                 #     |............|         |...............| |\n"
    "|            ###################     |............|   ######+...............| |\n"
    "|            #                 #     |............|   #     |...............| |\n"
    "|            #                 #     |-----+------|   #     |--------+------| |\n"
    "|  |---------+-----------|     #           #          #              #        |\n"
    "|  |.....................|     #           #          #         |----+------| |\n"
    "|  |.....................|     ########################         |...........| |\n"
    "|  |.....................|     #           #                    |...........| |\n"
    "|  |.....................|     #    |------+--------------------|...........| |\n"
    "|  |.....................|     #    |.......................................| |\n"
    "|  |.....................+##########+.......................................| |\n"
    "|  |.....................|          |.......................................| |\n"
    "|  |---------------------|          |---------------------------------------| |\n"
    "|                                                                             |\n"
    "|-----------------------------------------------------------------------------|";
}
