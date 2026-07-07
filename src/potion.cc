export module potion;

import <algorithm>;
import player;

export class Potion {
    public:
    virtual void apply(Player& p) = 0;
    void interact(Player& p) { apply(p); }
};

export class RH : public Potion {
    public:
    void apply(Player& p) { p.hp = std::min(p.maxHp, p.hp + 10); }
};
export class BA : public Potion {
    public:
    void apply(Player& p) { p.atk += 5; }
};
export class BD : public Potion {
    public:
    void apply(Player& p) { p.def += 5; }
};
export class PH : public Potion {
    public:
    void apply(Player& p) { p.hp = std::max(0, p.hp - 10); }
};
export class WA : public Potion {
    public:
    void apply(Player& p) { p.atk = std::max(0, p.atk - 5); }
};
export class WD : public Potion {
    public:
    void apply(Player& p) { p.def = std::max(0, p.def - 5); }
};