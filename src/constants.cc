export module constants;

export namespace constants {
    // Board features
    namespace board {
        // Board dimensions
        constexpr int HEIGHT{79};
        constexpr int WIDTH{30};

        // Max x/y positions: DO NOT MODIFY
        constexpr int MAX_Y = HEIGHT - 1;
        constexpr int MAX_X = WIDTH - 1;
    }
    
    // Character symbols
    namespace symbol {
        constexpr char PLAYER = '@';
        
        namespace enemy {
            constexpr char HUMAN = 'H';
            constexpr char DWARF = 'W';
            constexpr char ELF = 'E';
            constexpr char ORC = 'O';
            constexpr char MERCHANT = 'M';
            constexpr char DRAGON = 'D';
            constexpr char HALFLING = 'L';
        }
    }
}
