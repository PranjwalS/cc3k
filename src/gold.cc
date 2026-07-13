export module gold;

export class Gold {
    int x, y;
    int value;
    bool dragonGuarded;
    
    public:
    Gold(int x, int y, int value, bool dragonGuarded = false) : 
        x{x}, y{y}, value{value}, dragonGuarded{dragonGuarded} {
            // f.addGold(x, y, indice?? need to add to game.gold first to get an indice)
        }
};
