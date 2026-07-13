export module gold;
import floor;

export class Gold {
    int x, y;
    int value;
    bool dragonGuarded;
    
    public:
    Gold(int x, int y, int value, Floor& f, bool dragonGuarded = false) : 
        value{value} {
            // f.addGold(x, y, indice?? need to add to game.gold first to get an indice)
        }
};
