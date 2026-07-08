export module constants;

import <optional>;

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
    
    namespace race {
        // Enums with symbol representations
        enum class Player : char {
            Shade = '@',
            Drow = '@',
            Vampire = '@',
            Troll = '@',
            Goblin = '@'
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

        constexpr char enemyToChar(Enemy e) { return static_cast<char>(e); }

        constexpr std::optional<Enemy> charToEnemy(char c) {
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
    }
}
