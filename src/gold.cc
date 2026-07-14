export module gold;

export class Gold {
    int value;
    bool dragonGuarded;
    
    public:
    Gold(int value, bool dragonGuarded = false) : value{value}, dragonGuarded{dragonGuarded} {}
    int getValue() const { return value; }
    int isDragonGuarded() const { return dragonGuarded; }
};

export int randomGold();
