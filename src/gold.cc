export module gold;

export class Gold {
    public:
    int value;
    bool dragonGuarded = false;
    Gold(int value) : value{value} {}
};