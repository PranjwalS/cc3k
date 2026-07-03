export module enemy;

import character;
class Floor;

export class Enemy : public Character {
    public:
    Floor& drop(Floor& m);
};
