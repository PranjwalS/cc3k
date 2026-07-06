export module enemy;

import random;
import character;
class Floor;

export class Enemy : public Character {
    public:
    Floor& drop(Floor& m);
    Enemy(int hp, int atk, int def, Floor& m) : 
        hp{hp}, atk{atk}, def{def} {
            spawn(m);
        }
};
export class Human : public Enemy;
export class Dwarf : public Enemy;
export class Vampire : public Enemy;
export class Elf : public Enemy;
export class Orc : public Enemy;
export class Merchant : public Enemy;
export class Halfling : public Enemy;